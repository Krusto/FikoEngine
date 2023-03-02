#pragma once

#include "Renderer/Texture.h"

namespace FikoEngine {
    class VulkanTexture : public Texture {
    public:
        VulkanTexture(std::string_view Path);

        VulkanTexture(char *data, u32 channels, u32 width, u32 height);

        virtual void Load(std::string_view Path) override;

        virtual void Load(char *data, u32 channels, u32 width, u32 height) override;

        virtual void Bind(u32 slot = 0) const override;

        virtual void Destroy() override;

    };
}