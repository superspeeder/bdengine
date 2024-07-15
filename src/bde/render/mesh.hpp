#pragma once

#include <memory>
#include <vector>

#include "bde/hal.hpp"
#include "bde/render/interfaces.hpp"

#include <glm/glm.hpp>

namespace bde::render {

    struct StandardVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec4 color;
    };

    struct MeshData {
        std::vector<StandardVertex> vertices;
        std::vector<unsigned int> indices;
    };

    class Mesh final : public Renderable {
      public:
        Mesh(const MeshData &meshData);
        ~Mesh() override;


      private:
        std::unique_ptr<hal::Buffer>      m_VertexBuffer;
        std::unique_ptr<hal::Buffer>      m_IndexBuffer;
        std::unique_ptr<hal::VertexArray> m_VertexArray;
    };

} // namespace bde::render
