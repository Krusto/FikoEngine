#include <Core/Ref.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/OpenGL/OpenGLFramebuffer.h>
#include <Renderer/Vulkan/Framebuffer.h>
#include "Framebuffer.h"

namespace FikoEngine {
    Ref<Framebuffer> Framebuffer::Create(u32 width, u32 height) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanFramebuffer>::Create(width,height);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLFramebuffer>::Create(width,height);
            default:
                return nullptr;
        }
    }
}