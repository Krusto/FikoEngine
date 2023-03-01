#include "VertexBuffer.h"
#include "Renderer/OpenGL/OpenGLVertexBuffer.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexBuffer.h>

namespace FikoEngine {

    Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout &layout, Vertex *data, u32 length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
<<<<<<< HEAD
                return Ref<OpenGLVertexBuffer>::Create(layout,data,length);
            case RendererAPI::API::Vulkan:
                return Ref<VulkanVertexBuffer>::Create(layout, data, length);
=======
                return Ref<VulkanVertexBuffer>::Create(layout, data, length);
                break;
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
            default:
                return nullptr;
        }
    }

    Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout &layout, float *data, u32 length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanVertexBuffer>::Create(layout, data, length);
            case RendererAPI::API::OpenGL:
<<<<<<< HEAD
                return Ref<OpenGLVertexBuffer>::Create(layout, data, length);
=======
                return Ref<VulkanVertexBuffer>::Create(layout, data, length);
                break;
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
            default:
                return nullptr;
        }
    }

}