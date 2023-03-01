#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "./image/stb_image.h"
#include <cstdint>
#include <string_view>
#include <vector>
#include <Renderer/Texture.h>


class OpenGLTexture : public Texture {
public:
    virtual ~OpenGLTexture() override{}
    OpenGLTexture(std::string_view Path) { Load(Path); }
    OpenGLTexture(unsigned char* data, uint32_t channels, uint32_t width, uint32_t height, uint32_t xOffset = 0, uint32_t yOffset = 0) { this->Load(data, channels, width, height,xOffset,yOffset); }
    virtual void Load(std::string_view Path) override;
    virtual void Load(unsigned char* data, uint32_t channels, uint32_t width, uint32_t height, uint32_t xOffset = 0, uint32_t yOffset = 0) override;
    virtual void Bind(uint32_t slot = 0) const override;
    virtual void Destroy() override;

    virtual uint32_t& ID() override{ return m_id; };
    virtual uint32_t width() override{ return m_width; }
    virtual uint32_t height() override { return m_height; }
    virtual uint32_t channels() override { return m_channels; }

    virtual TextureType GetType() override { return TextureType::Texture2D; }
    virtual const TextureType GetType() const override { return TextureType::Texture2D; };

    virtual std::string GetName() override { return m_name; };

    virtual TextureState GetState() override { return m_State; }
    virtual void SetState(TextureState state) { m_State = state; }

protected:
    uint32_t m_id;
    int m_width;
    int m_height;
    int m_channels;
    std::string m_name;
    TextureState m_State = TextureState::Unloaded;
};

class OpenGLSkyboxTexture {
public:
    OpenGLSkyboxTexture() = default;
    explicit OpenGLSkyboxTexture(std::string_view Path);

    static OpenGLSkyboxTexture Create(std::string_view Path){return OpenGLSkyboxTexture{Path};}

    void Load(std::vector<std::string> Path);

    void Bind() const;

    void Destroy();

    uint32_t id{};
    int width{};
    int height{};
    int channels{};
private:
};