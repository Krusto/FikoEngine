//
// Created by KSTOYAN2 on 6/12/2022.
//
#include "Renderpass.h"
#include "../Memory.h"

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
}