//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//

#include "Framebuffer.h"
#include "Memory.h"
#include "RendererData.h"
#include "VulkanRenderer.h"

namespace FikoEngine {

    std::vector<VkFramebuffer> CreateFramebuffers(VkDevice device,Ref<Swapchain> swapchain,VkRenderPass renderPass) {
        std::vector<VkFramebuffer> framebuffers(swapchain->FramesCount);
        swapchain->GetSwapchainSpec().frameSize.width = swapchain->GetSwapchainSpec().imageExtent.width;
        swapchain->GetSwapchainSpec().frameSize.height = swapchain->GetSwapchainSpec().imageExtent.height;

        for (u32 i = 0; i < framebuffers.size(); ++i) {
            VkFramebufferCreateInfo framebufferInfo{.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = &swapchain->GetImageViews()[i];
            framebufferInfo.width = swapchain->GetSwapchainSpec().frameSize.width;
            framebufferInfo.height = swapchain->GetSwapchainSpec().frameSize.height;
            framebufferInfo.layers = 1;

            VK_CHECK(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffers[i]));
        }

        return framebuffers;
    }

    uint32_t VulkanFramebuffer::GetID() {
        return {};
    }

    uint32_t &VulkanFramebuffer::GetColorAttachmentID() {
        return m_color_texture;
    }

    void VulkanFramebuffer::Resize(uint32_t width, uint32_t height) {
        Destroy();

        Init(width,height);
    }

    void VulkanFramebuffer::Destroy() {
        for (auto& buffer : m_Framebuffers)
            vkDestroyFramebuffer(VulkanRenderer::s_RendererData.device,buffer,nullptr);
    }

    void VulkanFramebuffer::Bind() {
        VulkanRenderer::s_RendererData.framebuffer = Ref<VulkanFramebuffer>(this);
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
         m_Framebuffers = CreateFramebuffers(VulkanRenderer::s_RendererData.device,VulkanRenderer::s_RendererData.swapchain,VulkanRenderer::s_RendererData.renderPass);

    }
}