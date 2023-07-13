#pragma once

#include "Renderer/Texture.h"

namespace FikoEngine {
    class VulkanTexture : public Texture {
    public:
        explicit VulkanTexture(std::string_view Path);

        VulkanTexture(char *data, uint32_t channels, uint32_t width, uint32_t height);

        void Load(std::string_view Path) override;

        void Load(char *data, uint32_t channels, uint32_t width, uint32_t height) override;

        void Bind(uint32_t slot = 0) const override;

        void Destroy() override;

    };
}