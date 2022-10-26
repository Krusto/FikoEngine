//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//

#include "Framebuffer.h"
#include "Memory.h"
#include "RendererData.h"
#include "VulkanContext.h"

namespace FikoEngine {

    std::vector<VkFramebuffer> CreateFramebuffers(VkDevice device,Swapchain& swapchain,u32 width, u32 height) {
        std::vector<VkFramebuffer> framebuffers(swapchain.FramesCount);

        for (u32 i = 0; i < framebuffers.size(); ++i) {
            VkFramebufferCreateInfo framebufferInfo{.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
            framebufferInfo.renderPass = swapchain.Renderpass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = &swapchain.ImageViews[i];
            framebufferInfo.width = swapchain.FrameSize.width;
            framebufferInfo.height = swapchain.FrameSize.height;
            framebufferInfo.layers = 1;

            VK_CHECK(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffers[i]));
            LOG_INFO("Created framebuffer with index: " + std::to_string(i));
        }
        LOG_INFO("Successfully created framebuffers with size [" +
        std::to_string(width) + "," + std::to_string(height) + "]!");

        return framebuffers;
    }

    uint32_t VulkanFramebuffer::GetID() {
        return {};
    }

    uint32_t &VulkanFramebuffer::GetColorAttachmentID() {
        return m_color_texture;
    }

    void VulkanFramebuffer::Resize(uint32_t width, uint32_t height) {

    }

    void VulkanFramebuffer::Destroy() {

    }

    void VulkanFramebuffer::Bind() {

    }

    void VulkanFramebuffer::Unbind() {

    }

    uint32_t VulkanFramebuffer::width() {
        return m_width;
    }

    uint32_t VulkanFramebuffer::height() {
        return m_height;
    }

    ViewportSize VulkanFramebuffer::GetViewportSize() {
        return {m_width,m_height};
    }

    void VulkanFramebuffer::Init(u32 width, u32 height) {
         m_width = width;
         m_height = height;

         static_cast<Swapchain*>(m_Swapchain)->Framebuffers = CreateFramebuffers(VulkanContext::s_RendererData.device,*static_cast<Swapchain*>(m_Swapchain),width,height);
    }
}