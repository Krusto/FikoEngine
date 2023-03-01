#include "Texture.h"
#include "Renderer/OpenGL/OpenGLTexture.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/Texture.h>
namespace FikoEngine {
    Ref<Texture> Texture::Create(std::string_view Path) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanTexture>::Create(Path);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLTexture>::Create(Path);
            default:
                return nullptr;
        }
    }

    Ref<Texture> Texture::Create(char *data, uint32_t channels, uint32_t width, uint32_t height) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanTexture>::Create(data, channels, width, height);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLTexture>::Create(data, channels, width, height);
            default:
                return nullptr;
        }
    }
}