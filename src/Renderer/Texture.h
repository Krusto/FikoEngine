#pragma once
#include <string>
#include <Core/Ref.h>
enum class TextureType {
    None,Texture2D,TextureCube
};
class Texture : public RefCounted {
public:
    static Ref<Texture> Create(std::string_view Path);
    static Ref<Texture> Create(char* data, uint32_t channels, uint32_t width, uint32_t height);

    virtual ~Texture() {};
    virtual void Load(std::string_view Path) = 0;
    virtual void Load(char* data, uint32_t channels, uint32_t width, uint32_t height) = 0;
    virtual void Bind(uint32_t slot = 0) const = 0;

    virtual void Destroy() = 0;
    virtual uint32_t ID() = 0;
    virtual uint32_t width() = 0;
    virtual uint32_t height() = 0;
    virtual uint32_t channels() = 0;
    virtual TextureType GetType() = 0;
    virtual const TextureType GetType() const = 0;
};