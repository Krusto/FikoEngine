#include <Scene/Entity.h>
#include <Scene/Component.h>
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/MeshBuilder.h"
#include "Renderer/Vulkan/VertexBuffer.h"

namespace FikoEngine {
    DrawableComponent DrawableComponent::Generate(Entity entity) {
        const auto &mesh = entity.GetComponent<MeshComponent>().mesh;

        DrawableComponent output;
        output.va = VertexArray::Create((uint32_t) mesh.indices.size());
        output.va->Bind();

        output.va->AddVertexBuffer(VertexBuffer::Create(Vertex::GetLayout(),(float*)&mesh.vertices[0],(uint32_t)mesh.vertices.size()));
        output.va->AddIndexBuffer(IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size()));

        output.va->Unbind();

        return output;
    }

    DrawableComponent::~DrawableComponent() = default;

    MeshComponent MeshComponent::Generate(MeshType type) {
        auto mesh = MeshBuilder::CreateMesh(type);

        MeshComponent output;
        output.type = type;

        output.va = VertexArray::Create((uint32_t) mesh.indices.size());
        output.va->Bind();

        output.va->AddVertexBuffer(VertexBuffer::Create(Vertex::GetLayout(),(float*)&mesh.vertices[0],(uint32_t)mesh.vertices.size()));
        output.va->AddIndexBuffer(IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size()));

        output.va->Unbind();

        return output;
    }

}