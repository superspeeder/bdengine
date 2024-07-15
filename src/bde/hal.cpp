#include "hal.hpp"

namespace bde::hal {
    std::unique_ptr<Buffer> Buffer::create_unique(size_t size, const void *data, BufferUsage usage) {
        return std::make_unique<Buffer>(size, data, usage);
    }

    std::shared_ptr<Buffer> Buffer::create_shared(size_t size, const void *data, BufferUsage usage) {
        return std::make_shared<Buffer>(size, data, usage);
    }

    Buffer::Buffer(size_t size, const void *data, BufferUsage usage) : m_CurrentUsage(usage), m_CurrentSize(size) {
        glCreateBuffers(1, &m_Buffer);
        setData(size, data, usage);
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1, &m_Buffer);
    }

    void Buffer::bind(const BufferTarget &target) const {
        glBindBuffer((GLenum)target, m_Buffer);
    }

    void Buffer::bind(const IndexedBufferTarget &target, unsigned int index) const {
        glBindBufferBase((GLenum)target, index, m_Buffer);
    }

    void Buffer::bindRange(const IndexedBufferTarget &target, unsigned int index, ssize_t offset, size_t size) const {
        glBindBufferRange((GLenum)target, index, m_Buffer, offset, (ssize_t)size);
    }

    void Buffer::invalidate() const {
        glInvalidateBufferData(m_Buffer);
    }

    void Buffer::setData(size_t size, const void *data, BufferUsage usage) {
        glNamedBufferData(m_Buffer, (ssize_t)size, data, (GLenum)usage);
        m_CurrentUsage = usage;
        m_CurrentSize  = size;
    }

    void Buffer::setSubData(ssize_t offset, size_t size, const void *data) const {
        glNamedBufferSubData(m_Buffer, offset, (ssize_t)size, data);
    }

    VertexArray::VertexArray() {
        glCreateVertexArrays(1, &m_VertexArray);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_VertexArray);
    }

    void VertexArray::bind() {
        glBindVertexArray(m_VertexArray);
    }

    void VertexArray::vertexBuffer(unsigned int handle, const std::vector<VertexAttribute> &attributes, size_t stride, ssize_t offset) {
        unsigned int binding = m_NextBindingIndex++;
        glVertexArrayVertexBuffer(m_VertexArray, binding, handle, offset, stride);

        for (const auto &adesc : attributes) {
            unsigned int attribute = m_NextAttributeIndex++;
            glVertexArrayAttribBinding(m_VertexArray, attribute, binding);
            if (adesc.pureInteger) {
                glVertexArrayAttribIFormat(m_VertexArray, attribute, (GLint)adesc.size, (GLenum)adesc.dataType, adesc.offset);
            } else if (adesc.dataType == VertexDataType::Double) {
                glVertexArrayAttribLFormat(m_VertexArray, attribute, (GLint)adesc.size, GL_DOUBLE, adesc.offset);
            } else {
                glVertexArrayAttribFormat(m_VertexArray, attribute, (GLint)adesc.size, (GLenum)adesc.dataType, adesc.normalized, adesc.offset);
            }

            enableAttribute(attribute);
        }
    }

    void VertexArray::enableAttribute(unsigned int attribute) const {
        glEnableVertexArrayAttrib(m_VertexArray, attribute);
    }

    void VertexArray::disableAttribute(unsigned int attribute) const {
        glDisableVertexArrayAttrib(m_VertexArray, attribute);
    }

    void VertexArray::elementBuffer(unsigned int handle) {
        glVertexArrayElementBuffer(m_VertexArray, handle);
        m_HasElementBuffer = handle == 0;
    }
} // namespace bde::hal
