#include "Texture.h"

namespace FikoEngine {
    VulkanTexture::VulkanTexture(std::string_view Path){}

    VulkanTexture::VulkanTexture(char *data, uint32_t channels, uint32_t width, uint32_t height){}

    void VulkanTexture::Load(std::string_view Path){}

    void VulkanTexture::Load(char *data, uint32_t channels, uint32_t width, uint32_t height){}

    void VulkanTexture::Bind(uint32_t slot) const {}

    void VulkanTexture::Destroy(){}

    uint32_t VulkanTexture::ID(){ return {};}

    uint32_t VulkanTexture::width(){ return {};}

    uint32_t VulkanTexture::height(){ return {};}

    uint32_t VulkanTexture::channels(){ return {};}

    TextureType VulkanTexture::GetType(){ return {};}

    const TextureType VulkanTexture::GetType() const{ return {};}
}