#include "Texture.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/Texture.h>
namespace FikoEngine {
    Ref<Texture> Texture::Create(std::string_view Path) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanTexture>::Create(Path);
            default:
                exit(-1);
                break;
        }
    }

    Ref<Texture> Texture::Create(char *data, uint32_t channels, uint32_t width, uint32_t height) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanTexture>::Create(data, channels, width, height);
            default:
                exit(-1);
                break;
        }
    }
}