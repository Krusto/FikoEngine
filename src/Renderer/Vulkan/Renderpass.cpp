//
// Created by Stoyanov, Krusto (K.S.) on 6/12/2022.
//
#include "Renderpass.h"
#include "Memory.h"

namespace FikoEngine{
    VkRenderPass CreateRenderPass(RendererDataAPI& rendererData){
        VkRenderPass renderPass{};

        VkRenderPassCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};

        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = rendererData.swapChainSpec.imageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        createInfo.attachmentCount = 1;
        createInfo.pAttachments = &colorAttachment;
        createInfo.subpassCount = 1;
        createInfo.pSubpasses = &subpass;

        VK_CHECK(vkCreateRenderPass(rendererData.device,&createInfo,CreatePAllocator("Renderpass"),&renderPass));

        LOG_INFO("RenderPass created successfully!");

        return renderPass;
    }
    void BeginRenderPass(RendererDataAPI& rendererData, u32 index){
        VkRenderPassBeginInfo renderPassInfo{.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        renderPassInfo.renderPass = rendererData.renderPass;
        renderPassInfo.framebuffer = rendererData.swapChainFramebuffers[index];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = rendererData.swapChainSpec.imageExtent;

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(rendererData.commandBuffers[index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        LOG_INFO("Beginning render pass on command buffer " + std::to_string(index) + "!");
    }
    void EndRenderPass(RendererDataAPI& rendererData,u32 index){
        vkCmdEndRenderPass(rendererData.commandBuffers[index]);
    }


}