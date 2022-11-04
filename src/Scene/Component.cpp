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
        auto vb = VertexBuffer::Create(Vertex::GetLayout(), (float *) mesh.vertices.data(),
                                       (uint32_t) mesh.vertices.size());
        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());

        output.va->AddVertexBuffer(vb);
        output.va->AddIndexBuffer(ib);

        output.va->Unbind();

        return output;
    }

    MeshComponent MeshComponent::Generate(Entity entity, MeshType type) {
        auto mesh = MeshBuilder::CreateMesh(type);

        MeshComponent output;
        output.type = type;

        output.va = VertexArray::Create((uint32_t) mesh.indices.size());
        output.va->Bind();
        Ref<VertexBuffer> vb = Ref<VulkanVertexBuffer>::Create(Vertex::GetLayout(),  (float *) &mesh.vertices[0], (u32) mesh.vertices.size());
        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());

        output.va->AddVertexBuffer(vb);
        output.va->AddIndexBuffer(ib);

        output.va->Unbind();

        return output;
    }
}
