#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "./image/stb_image.h"
#include <cstdint>
#include <string_view>
#include <vector>
#include <Renderer/Texture.h>

namespace FikoEngine {
    class OpenGLTexture : public Texture {
    public:
        ~OpenGLTexture() {}

        OpenGLTexture(std::string_view Path) { Load(Path); }

        OpenGLTexture(char *data, u32 channels, u32 width, u32 height)
        { this->Load(data, channels, width, height); }

        virtual void Load(std::string_view Path) override;

        virtual void Load(char *data, u32 channels, u32 width, u32 height) override;

        virtual void Bind(u32 slot = 0) const override;

        virtual void Destroy() override;

    };

    class OpenGLSkyboxTexture {
    public:
        OpenGLSkyboxTexture() = default;

        explicit OpenGLSkyboxTexture(std::string_view Path);

        static OpenGLSkyboxTexture Create(std::string_view Path) { return OpenGLSkyboxTexture{Path}; }

        void Load(std::vector<std::string> Path);

        void Bind() const;

        void Destroy();

        u32 id{};
        int width{};
        int height{};
        int channels{};
    private:
    };
}