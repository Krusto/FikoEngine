#include "VertexArray.h"
#include "Renderer/OpenGL/OpenGLVertexArray.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexArray.h>

namespace FikoEngine {

    Ref<VertexArray> VertexArray::Create(u32 indexCount) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanVertexArray>::Create(indexCount);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLVertexArray>::Create(indexCount);
            default:
                return nullptr;
        }
    }

    void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
        Bind();
        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::AddIndexBuffer(Ref<IndexBuffer> indexBuffer) {
        m_IndexBuffer = indexBuffer;
    }
}