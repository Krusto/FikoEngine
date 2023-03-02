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

        static Ref<Texture> Create(char *data, u32 channels, u32 width, u32 height);

        virtual void Load(std::string_view Path) = 0;

        virtual void Load(char *data, u32 channels, u32 width, u32 height) = 0;

        virtual void Bind(u32 slot = 0) const = 0;

        virtual void Destroy() = 0;

        std::string GetName() { return m_Name; };

        TextureState GetState() { return m_State;};

        void SetState(TextureState state) { m_State = state; }

        u32 &ID() { return m_id; };

        u32 width() { return m_width; }

        u32 height() { return m_height; }

        u32 channels() { return m_channels; }

        TextureType GetType() { return TextureType::Texture2D; }

        const TextureType GetType() const { return TextureType::Texture2D; };

    protected:
        std::string m_Name;
        TextureState m_State = TextureState::Unloaded;
        u32 m_id;
        int m_width;
        int m_height;
        int m_channels;
    };
}