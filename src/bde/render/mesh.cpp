#include "mesh.hpp"

namespace bde::render {
    Mesh::Mesh(const MeshData &meshData) {
        m_VertexBuffer = hal::Buffer::create_unique(meshData.vertices, hal::BufferUsage::StaticDraw);
    }

    Mesh::~Mesh() {

    }
} // namespace bde::render
