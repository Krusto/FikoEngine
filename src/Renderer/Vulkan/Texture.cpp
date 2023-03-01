#include "Texture.h"

namespace FikoEngine {
    VulkanTexture::VulkanTexture(std::string_view Path){}

    VulkanTexture::VulkanTexture(char *data, uint32_t channels, uint32_t width, uint32_t height){}

    void VulkanTexture::Load(std::string_view Path){}

    void VulkanTexture::Load(char *data, uint32_t channels, uint32_t width, uint32_t height){}

    void VulkanTexture::Bind(uint32_t slot) const {}

    void VulkanTexture::Destroy(){}

}