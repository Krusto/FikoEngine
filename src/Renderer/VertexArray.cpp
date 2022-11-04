#include "VertexArray.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexArray.h>

namespace FikoEngine {

    Ref<VertexArray> VertexArray::Create(uint32_t indexCount) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanVertexArray>::Create(indexCount);
                break;
            default:
                exit(-1);
                break;
        }
    }
    void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer){
        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::AddIndexBuffer(Ref<IndexBuffer> indexBuffer){
    m_IndexBuffer = indexBuffer;
    }

}