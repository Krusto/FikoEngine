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
}