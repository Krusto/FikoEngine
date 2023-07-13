#include "VertexBuffer.h"
#include "Renderer/OpenGL/OpenGLVertexBuffer.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/VertexBuffer.h>

namespace FikoEngine {

    Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout &layout, Vertex *data, uint32_t length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VertexBuffer>(new VulkanVertexBuffer(layout, data, length));
            case RendererAPI::API::OpenGL:
                return Ref<VertexBuffer>(new OpenGLVertexBuffer(layout,data,length));
            default:
                return nullptr;
        }
    }

    Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout &layout, float *data, uint32_t length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VertexBuffer>(new VulkanVertexBuffer(layout, data, length));
            case RendererAPI::API::OpenGL:
                return Ref<VertexBuffer>(new OpenGLVertexBuffer(layout,data,length));
            default:
                return nullptr;
        }
    }

}