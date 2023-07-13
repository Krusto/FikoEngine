#include "GraphicsContext.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/OpenGL/OpenGLContext.h>
#include "Renderer/Vulkan/VulkanContext.h"
GraphicsContext* GraphicsContext::s_Context;
GraphicsContext* GraphicsContext::Create(GLFWwindow* window)
{
    switch (FikoEngine::RendererAPI::Current()) {
        case FikoEngine::RendererAPI::API::OpenGL: {
            auto context = new OpenGLContext(window);
            context->window = window;
            return context;
        }
        case FikoEngine::RendererAPI::API::Vulkan:
            return new VulkanContext(window);
        default:
            return nullptr;
    }
}
