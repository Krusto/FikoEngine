//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <Core/Core.h>
#include <Core/Ref.h>

#include <Renderer/Framebuffer.h>
#include <Renderer/Viewport.h>

#include "RendererData.h"
#include "Swapchain.h"

namespace FikoEngine{
    class VulkanFramebuffer : public Framebuffer{
    public:
        VulkanFramebuffer(uint32_t width, uint32_t height) { Init(width, height); }
        void Init(uint32_t width,uint32_t height);

        virtual uint32_t GetID() override;

        virtual uint32_t &GetColorAttachmentID() override;

        virtual void Resize(u32 width, u32 height) override;

        virtual void Destroy() override;

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual uint32_t width() override;

        virtual uint32_t height() override;

        virtual ViewportSize GetViewportSize() override;

    private:
        u32 m_width{};
        u32 m_height{};
        u32 m_fbo{};
        u32 m_color_texture{};
        u32 m_depth_texture{};
        void* m_Swapchain;
    };

    std::vector<VkFramebuffer> CreateFramebuffers(VkDevice device,Swapchain& swapchain,u32 width, u32 height);
}