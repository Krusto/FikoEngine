#include "Texture.h"

namespace FikoEngine {
    VulkanTexture::VulkanTexture(std::string_view Path){}

    VulkanTexture::VulkanTexture(char *data, u32 channels, u32 width, u32 height){}

    void VulkanTexture::Load(std::string_view Path){}

    void VulkanTexture::Load(char *data, u32 channels, u32 width, u32 height){}

    void VulkanTexture::Bind(u32 slot) const {}

    void VulkanTexture::Destroy(){}

}