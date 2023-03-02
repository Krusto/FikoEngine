#pragma once
#include <Core/Ref.h>
#include <Renderer/Viewport.h>

namespace FikoEngine {
    class Framebuffer : public RefCounted {
    public:
        static Ref<Framebuffer> Create(u32 width, u32 height);

        virtual u32 GetID() = 0;

        virtual u32 &GetColorAttachmentID() = 0;

        virtual void Resize(u32 width, u32 height) = 0;

        virtual void Destroy() = 0;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual u32 width() = 0;

        virtual u32 height() = 0;

        virtual ViewportSize GetViewportSize() = 0;

    };
}