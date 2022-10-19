#include <Scene/Entity.h>
#include <Scene/Component.h>
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/MeshBuilder.h"

namespace FikoEngine {
    DrawableComponent DrawableComponent::Generate(Entity entity) {
        const auto &mesh = entity.GetComponent<MeshComponent>().mesh;

        DrawableComponent output;
        output.va = VertexArray::Create((uint32_t) mesh.indices.size());
        output.va->Bind();
        auto vb = VertexBuffer::Create(output.va, Vertex::GetLayout(), (float *) mesh.vertices.data(),
                                       (uint32_t) mesh.vertices.size());
        auto ib = IndexBuffer::Create(output.va, mesh.indices.data(), (uint32_t) mesh.indices.size());
        output.va->Unbind();

        return output;
    }

    MeshComponent MeshComponent::Generate(Entity entity, MeshType type) {
        const auto &mesh = MeshBuilder::CreateMesh(type);

        MeshComponent output;
        output.type = type;

        output.va = VertexArray::Create((uint32_t) mesh.indices.size());
        output.va->Bind();
        auto vb = VertexBuffer::Create(output.va, Vertex::GetLayout(), (float *) mesh.vertices.data(),
                                       (uint32_t) mesh.vertices.size());
        auto ib = IndexBuffer::Create(output.va, mesh.indices.data(), (uint32_t) mesh.indices.size());
        output.va->Unbind();

        return output;
    }
}
