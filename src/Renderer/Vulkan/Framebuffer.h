//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <Core/Core.h>
#include <Core/Ref.h>

#include <Renderer/Framebuffer.h>
#include <Renderer/Viewport.h>

#include "Swapchain.h"

namespace FikoEngine{
    class VulkanFramebuffer : public Framebuffer{
    public:
        VulkanFramebuffer(u32 width, u32 height) { Init(width, height); }
        void Init(u32 width,u32 height);

        virtual u32 GetID() override;

        virtual u32 &GetColorAttachmentID() override;

        virtual void Resize(u32 width, u32 height) override;

        virtual void Destroy() override;

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual u32 width() override;

        virtual u32 height() override;

        virtual ViewportSize GetViewportSize() override;

        auto& VulkanData() { return m_Framebuffers; }
    private:
        u32 m_width{};
        u32 m_height{};
        u32 m_fbo{};
        u32 m_color_texture{};
        u32 m_depth_texture{};

        std::vector<VkFramebuffer> m_Framebuffers;
    };

    std::vector<VkFramebuffer> CreateFramebuffers(VkDevice device,Ref<Swapchain> swapchain,VkRenderPass renderPass);
}