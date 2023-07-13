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
        static Texture* CreateRaw(std::string_view Path);

        static Ref<Texture> Create(char *data, uint32_t channels, uint32_t width, uint32_t height);

        virtual ~Texture() = default;

        virtual void Load(std::string_view Path) = 0;

        virtual void Load(char *data, uint32_t channels, uint32_t width, uint32_t height) = 0;

        virtual void Bind(uint32_t slot) const = 0;

        virtual void Destroy() = 0;

        std::string GetName() { return m_Name; };

        TextureState GetState() { return m_State;};

        void SetState(TextureState state) { m_State = state; }

        uint32_t &ID() { return m_id; };

        uint32_t width() const { return m_width; }

        uint32_t height() const { return m_height; }

        uint32_t channels() const { return m_channels; }

        TextureType GetType() const { return m_Type; }

    protected:
        std::string m_Name;
        TextureState m_State = TextureState::Unloaded;
        TextureType m_Type = TextureType::Texture2D;
        uint32_t m_id;
        int m_width;
        int m_height;
        int m_channels;
    };
}