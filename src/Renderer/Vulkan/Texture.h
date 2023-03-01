#pragma once

#include "Renderer/Texture.h"

namespace FikoEngine {
    class VulkanTexture : public Texture {
    public:
        VulkanTexture(std::string_view Path);

        VulkanTexture(char *data, uint32_t channels, uint32_t width, uint32_t height);

        virtual void Load(std::string_view Path) override;

        virtual void Load(char *data, uint32_t channels, uint32_t width, uint32_t height) override;

        virtual void Bind(uint32_t slot = 0) const override;

        virtual void Destroy() override;

    };
}