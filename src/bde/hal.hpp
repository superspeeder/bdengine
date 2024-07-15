#pragma once

#include <glad/gl.h>

#include <memory>
#include <variant>
#include <vector>

#include "bde/utils.hpp"

namespace bde::hal {
    enum class BufferUsage : GLenum {
        StaticDraw  = GL_STATIC_DRAW,
        StaticRead  = GL_STATIC_READ,
        StaticCopy  = GL_STATIC_COPY,
        StreamDraw  = GL_STREAM_DRAW,
        StreamRead  = GL_STREAM_READ,
        StreamCopy  = GL_STREAM_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY,
    };

    enum class BufferTarget : GLenum {
        Array             = GL_ARRAY_BUFFER,
        ElementArray      = GL_ELEMENT_ARRAY_BUFFER,
        Uniform           = GL_UNIFORM_BUFFER,
        ShaderStorage     = GL_SHADER_STORAGE_BUFFER,
        PixelPack         = GL_PIXEL_PACK_BUFFER,
        PixelUnpack       = GL_PIXEL_UNPACK_BUFFER,
        DispatchIndirect  = GL_DISPATCH_INDIRECT_BUFFER,
        DrawIndirect      = GL_DRAW_INDIRECT_BUFFER,
        CopyRead          = GL_COPY_READ_BUFFER,
        CopyWrite         = GL_COPY_WRITE_BUFFER,
        AtomicCounter     = GL_ATOMIC_COUNTER_BUFFER,
        Texture           = GL_TEXTURE_BUFFER,
        Query             = GL_QUERY_BUFFER,
        TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
    };

    enum class IndexedBufferTarget : GLenum {
        TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
        Uniform           = GL_UNIFORM_BUFFER,
        AtomicCounter     = GL_ATOMIC_COUNTER_BUFFER,
        ShaderStorage     = GL_SHADER_STORAGE_BUFFER,
    };

    enum class PrimitiveType : GLenum {
        Triangles              = GL_TRIANGLES,
        TriangleStrip          = GL_TRIANGLE_STRIP,
        TriangleFan            = GL_TRIANGLE_FAN,
        TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
        TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY,
        Points                 = GL_POINTS,
        Lines                  = GL_LINES,
        LineStrip              = GL_LINE_STRIP,
        LineLoop               = GL_LINE_LOOP,
        LinesAdjacency         = GL_LINES_ADJACENCY,
        LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY,
        Patches                = GL_PATCHES,
        Quads                  = GL_QUADS,
    };

    class Buffer {
      public:
        static std::unique_ptr<Buffer> create_unique(size_t size, const void *data, BufferUsage usage);
        static std::shared_ptr<Buffer> create_shared(size_t size, const void *data, BufferUsage usage);

        template <typename T>
        static std::unique_ptr<Buffer> create_unique(const std::vector<T> &v, BufferUsage usage) {
            return create_unique(v.size() * sizeof(T), v.data(), usage);
        };

        template <typename T>
        static std::unique_ptr<Buffer> create_shared(const std::vector<T> &v, BufferUsage usage) {
            return create_shared(v.size() * sizeof(T), v.data(), usage);
        };

        Buffer(size_t size, const void *data, BufferUsage usage);
        ~Buffer();

        void bind(const BufferTarget &target) const;
        void bind(const IndexedBufferTarget &target, unsigned int index) const;

        void bindRange(const IndexedBufferTarget &target, unsigned int index, ssize_t offset, size_t size) const;

        void invalidate() const;

        void setData(size_t size, const void *data, BufferUsage usage);

        inline void setData(size_t size, const void *data) { setData(size, data, m_CurrentUsage); };

        void setSubData(ssize_t offset, size_t size, const void *data) const;

        template <typename T>
        void setData(const std::vector<T> &data) {
            setData(data.size() * sizeof(T), data, m_CurrentUsage);
        };

        template <typename T>
        void setData(const std::vector<T> &data, BufferUsage usage) {
            setData(data.size() * sizeof(T), data, usage);
        };

        template <typename T>
        void setSubData(const std::vector<T> &data, ssize_t offset) const {
            setSubData(offset, data.size() * sizeof(T), data);
        };

        inline unsigned int getHandle() const noexcept { return m_Buffer; }

      private:
        unsigned int m_Buffer{};

        BufferUsage m_CurrentUsage;
        size_t      m_CurrentSize = 0;
    };

    enum class VertexDataType : GLenum {
        Byte      = GL_BYTE,
        Short     = GL_SHORT,
        Int       = GL_INT,
        Fixed     = GL_FIXED,
        Float     = GL_FLOAT,
        HalfFloat = GL_HALF_FLOAT,
        Double    = GL_DOUBLE,

        UnsignedByte  = GL_UNSIGNED_BYTE,
        UnsignedShort = GL_UNSIGNED_SHORT,
        UnsignedInt   = GL_UNSIGNED_INT,

        Int2_10_10_10_Rev          = GL_INT_2_10_10_10_REV,
        UnsignedInt2_10_10_10_Rev  = GL_UNSIGNED_INT_2_10_10_10_REV,
        UnsignedInt10F_11F_11F_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV,
    };

    constexpr size_t sizeof_data_type(const VertexDataType &dt) {
        switch (dt) {
        case VertexDataType::Byte:
            return sizeof(GLbyte);
        case VertexDataType::Short:
            return sizeof(GLshort);
        case VertexDataType::Int:
            return sizeof(GLint);
        case VertexDataType::Fixed:
            return sizeof(GLfixed);
        case VertexDataType::Float:
            return sizeof(GLfloat);
        case VertexDataType::HalfFloat:
            return sizeof(GLhalf);
        case VertexDataType::Double:
            return sizeof(GLdouble);
        case VertexDataType::UnsignedByte:
            return sizeof(GLubyte);
        case VertexDataType::UnsignedShort:
            return sizeof(GLushort);
        case VertexDataType::UnsignedInt:
        case VertexDataType::Int2_10_10_10_Rev:
        case VertexDataType::UnsignedInt2_10_10_10_Rev:
        case VertexDataType::UnsignedInt10F_11F_11F_Rev:
            return sizeof(GLuint);
        }
    }

    struct VertexAttribute {
        VertexDataType dataType;
        ssize_t        offset;
        uint8_t        size;
        bool           normalized  = false;
        bool           pureInteger = false;
    };

    class VertexArray {
      public:
        VertexArray();
        ~VertexArray();

        static std::unique_ptr<VertexArray> create_unique() { return std::make_unique<VertexArray>(); }

        static std::shared_ptr<VertexArray> create_shared() { return std::make_shared<VertexArray>(); }

        void bind();

        void vertexBuffer(unsigned int handle, const std::vector<VertexAttribute> &attributes, size_t stride, ssize_t offset = 0);

        template <bde::utils::tptr<Buffer> B>
        void vertexBuffer(const B &buffer, const std::vector<VertexAttribute> &attributes, size_t stride, ssize_t offset = 0) {
            vertexBuffer(buffer->getHandle(), attributes, stride, offset);
        };

        void elementBuffer(unsigned int handle);

        template <bde::utils::tptr<Buffer> B>
        void elementBuffer(const B &buffer) {
            bindElementBuffer(buffer->getHandle());
        };

        void enableAttribute(unsigned int attribute) const;
        void disableAttribute(unsigned int attribute) const;

      private:
        unsigned int m_VertexArray;

        unsigned int m_NextAttributeIndex = 0;
        unsigned int m_NextBindingIndex   = 0;

        bool m_HasElementBuffer = false;
    };

    class ShaderModule {
      public:
        ShaderModule();
        ~ShaderModule();

        inline unsigned int getHandle() const noexcept { return m_Handle; };

      private:
        unsigned int m_Handle;
    };

    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Compute = GL_COMPUTE_SHADER,
        Mesh = GL_MESH_SHADER_NV,
        Task = GL_TASK_SHADER_NV,
    };

    struct ShaderSourceDefinition {
        bde::utils::source_definition source;
        ShaderType type;
    };

    using ShaderDefinition = std::variant<ShaderSourceDefinition, std::shared_ptr<ShaderModule>>;

    class ShaderProgram {
      public:
        ShaderProgram(const std::vector<ShaderDefinition> shaderModules);
        ~ShaderProgram();

        void use();

        [[nodiscard]] int getUniformLocation(const std::string_view& name);

        inline unsigned int getHandle() const noexcept { return m_Handle; };

      private:
        unsigned int m_Handle;
    };
} // namespace bde::hal
