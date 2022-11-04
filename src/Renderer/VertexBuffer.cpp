#include "VertexBuffer.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexBuffer.h>

namespace FikoEngine {

    Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout &layout, Vertex *data, u32 length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
                return Ref<VulkanVertexBuffer>::Create(layout, data, length);
                break;
            default:
                exit(-1);
                break;
        }
    }

    Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout &layout, float *data, u32 length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
                return Ref<VulkanVertexBuffer>::Create(layout, data, length);
                break;
            default:
                exit(-1);
                break;
        }
    }
}