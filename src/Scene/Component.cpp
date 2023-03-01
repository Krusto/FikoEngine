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
<<<<<<< HEAD

        output.va->AddVertexBuffer(VertexBuffer::Create(Vertex::GetLayout(),(float*)&mesh.vertices[0],(u32)mesh.vertices.size()));
//        auto vb = VertexBuffer::Create(Vertex::GetLayout(),(float*)&mesh.vertices[0],(u32)mesh.vertices.size());
        output.va->AddIndexBuffer(IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size()));
//        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());
=======
        auto vb = VertexBuffer::Create(Vertex::GetLayout(), (float *) mesh.vertices.data(),
                                       (uint32_t) mesh.vertices.size());
        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());

        output.va->AddVertexBuffer(vb);
        output.va->AddIndexBuffer(ib);
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650

        output.va->Unbind();

        return output;
    }

    MeshComponent MeshComponent::Generate(Entity entity, MeshType type) {
        auto mesh = MeshBuilder::CreateMesh(type);

        MeshComponent output;
        output.type = type;

        output.va = VertexArray::Create((uint32_t) mesh.indices.size());
        output.va->Bind();
<<<<<<< HEAD

        output.va->AddVertexBuffer(VertexBuffer::Create(Vertex::GetLayout(),(float*)&mesh.vertices[0],(u32)mesh.vertices.size()));
        output.va->AddIndexBuffer(IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size()));
//        auto vb = VertexBuffer::Create(Vertex::GetLayout(),(float*)&mesh.vertices[0],(u32)mesh.vertices.size());
//        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());
=======
        Ref<VertexBuffer> vb = Ref<VulkanVertexBuffer>::Create(Vertex::GetLayout(),  (float *) &mesh.vertices[0], (u32) mesh.vertices.size());
        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());

        output.va->AddVertexBuffer(vb);
        output.va->AddIndexBuffer(ib);
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650

        output.va->Unbind();

        return output;
    }
}