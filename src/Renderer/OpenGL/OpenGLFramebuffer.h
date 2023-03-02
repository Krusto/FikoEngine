#pragma once
#include <cstdint>
#include "../Framebuffer.h"
namespace FikoEngine {

    class OpenGLFramebuffer : public Framebuffer {
    public:
        OpenGLFramebuffer(u32 width, u32 height) { Init(width, height); }

        void Init(u32 width, u32 height);

        virtual u32 GetID() override;

        virtual u32 &GetColorAttachmentID() override;

        virtual void Resize(u32 width, u32 height) override;

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual void Destroy() override;

        virtual u32 width() override;

        virtual u32 height() override;

        virtual ViewportSize GetViewportSize() override { return {m_width, m_height}; }

    private:
        u32 m_width{};
        u32 m_height{};
        u32 m_fbo{};
        u32 m_color_texture{};
        u32 m_depth_texture{};
    };
}