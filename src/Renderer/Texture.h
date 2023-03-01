#pragma once
#include <string>
#include <Core/Ref.h>

namespace FikoEngine {

    enum class TextureType {
        None, Texture2D, TextureCube
    };
    enum class TextureState{
        None = 0,
        Loaded,
        Unloaded
    };
    class Texture : public RefCounted {
    public:
        static Ref<Texture> Create(std::string_view Path);

        static Ref<Texture> Create(char *data, uint32_t channels, uint32_t width, uint32_t height);

        virtual void Load(std::string_view Path) = 0;

        virtual void Load(char *data, uint32_t channels, uint32_t width, uint32_t height) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual void Destroy() = 0;

        std::string GetName() { return m_Name; };

        TextureState GetState() { return m_State;};

        void SetState(TextureState state) { m_State = state; }

        uint32_t &ID() { return m_id; };

        uint32_t width() { return m_width; }

        uint32_t height() { return m_height; }

        uint32_t channels() { return m_channels; }

        TextureType GetType() { return TextureType::Texture2D; }

        const TextureType GetType() const { return TextureType::Texture2D; };

    protected:
        std::string m_Name;
        TextureState m_State = TextureState::Unloaded;
        uint32_t m_id;
        int m_width;
        int m_height;
        int m_channels;
    };
}