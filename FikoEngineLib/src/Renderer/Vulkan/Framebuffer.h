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
        VulkanFramebuffer(uint32_t width, uint32_t height) { Init(width, height); }
        ~VulkanFramebuffer() = default;
        
        void Init(uint32_t width,uint32_t height);

        virtual uint32_t GetID() override;

        virtual uint32_t &GetColorAttachmentID() override;

        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual void Destroy() override;

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual uint32_t width() override;

        virtual uint32_t height() override;

        virtual ViewportSize GetViewportSize() override;

        auto& VulkanData() { return m_Framebuffers; }
    private:
        uint32_t m_width{};
        uint32_t m_height{};
        uint32_t m_fbo{};
        uint32_t m_color_texture{};
        uint32_t m_depth_texture{};

        std::vector<VkFramebuffer> m_Framebuffers;
    };

    std::vector<VkFramebuffer> CreateFramebuffers(VkDevice device,Ref<Swapchain> swapchain,VkRenderPass renderPass);
}