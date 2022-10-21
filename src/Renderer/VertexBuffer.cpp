#include "VertexBuffer.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexBuffer.h>

namespace FikoEngine {

    Ref<VertexBuffer>
    VertexBuffer::Create(Ref<VertexArray> va, const VertexLayout &layout, Vertex *data, uint32_t length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
                return Ref<VulkanVertexBuffer>::Create(va, layout, data, length);
                break;
            default:
                exit(-1);
                break;
        }
    }

    Ref<VertexBuffer>
    VertexBuffer::Create(Ref<VertexArray> va, const VertexLayout &layout, float *data, uint32_t length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
                return Ref<VulkanVertexBuffer>::Create(va, layout, data, length);
                break;
            default:
                exit(-1);
                break;
        }
    }
}