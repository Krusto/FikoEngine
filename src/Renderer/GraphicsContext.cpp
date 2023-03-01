#include "GraphicsContext.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/OpenGL/OpenGLContext.h>
#include "Renderer/Vulkan/VulkanContext.h"

Ref<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
{
    switch (FikoEngine::RendererAPI::Current()) {
        case FikoEngine::RendererAPI::API::OpenGL: {
            auto context = Ref<OpenGLContext>::Create(window);
            context->window = window;
            return context;
            break;
        }
        case FikoEngine::RendererAPI::API::Vulkan:
            return Ref<VulkanContext>::Create(window);
        default:
            return nullptr;
    }
    return nullptr;
}
