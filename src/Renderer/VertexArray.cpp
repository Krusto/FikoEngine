#include "VertexArray.h"
#include "Renderer/OpenGL/OpenGLVertexArray.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexArray.h>

namespace FikoEngine {

    Ref<VertexArray> VertexArray::Create(uint32_t indexCount) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanVertexArray>::Create(indexCount);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLVertexArray>::Create(indexCount);
            default:
                return nullptr;
        }
    }
<<<<<<< HEAD

    void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
        Bind();
        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::AddIndexBuffer(Ref<IndexBuffer> indexBuffer) {
        m_IndexBuffer = indexBuffer;
    }
=======
    void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer){
        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::AddIndexBuffer(Ref<IndexBuffer> indexBuffer){
    m_IndexBuffer = indexBuffer;
    }

>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
}