//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//

#include "Framebuffer.h"
#include "Memory.h"

namespace FikoEngine {
    VkFramebuffer CreateFramebuffer(RendererDataAPI &rendererData, u32 index) {
        VkFramebuffer framebuffer{};

        VkFramebufferCreateInfo framebufferInfo{.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
        framebufferInfo.renderPass = rendererData.renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = &rendererData.imageViews[index];
        framebufferInfo.width = rendererData.swapChainSpec.imageExtent.width;
        framebufferInfo.height = rendererData.swapChainSpec.imageExtent.height;
        framebufferInfo.layers = 1;

        VK_CHECK(vkCreateFramebuffer(rendererData.device, &framebufferInfo, CreatePAllocator("Framebuffer"), &framebuffer));
        LOG_INFO("Created framebuffer with index: " + std::to_string(index));
        return framebuffer;
    }

    std::vector<VkFramebuffer> CreateFramebuffers(RendererDataAPI &rendererData) {
        std::vector<VkFramebuffer> framebuffers(rendererData.imageViews.size());

        for (u32 i = 0; i < framebuffers.size(); ++i) {
            framebuffers[i] = CreateFramebuffer(rendererData,i);
        }
        LOG_INFO("Successfully created framebuffers with size [" +
        std::to_string(rendererData.swapChainSpec.imageExtent.width) + "," + std::to_string(rendererData.swapChainSpec.imageExtent.height) + "]!");

        return framebuffers;
    }
}