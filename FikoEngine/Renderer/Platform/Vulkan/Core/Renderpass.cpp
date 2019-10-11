//
// Created by krusto on 10/9/19.
//

#include "Renderpass.h"
#include "../VulkanUtilities.h"
namespace FikoEngine::VulkanRenderer {
    VkRenderPass RenderPass::CreateRenderpass(VkDevice device, VkSurfaceFormatKHR surfaceFormat) {
        VkRenderPass mRenderpass;

        createInfo.setAttachmentDescription(0, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_CLEAR,
                                            VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                            VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                                            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        createInfo.setAttachmentDescriptionAttr(0, surfaceFormat.format);

        VkAttachmentReference colorAttachments = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};

        createInfo.setSubpassDescription(0,
                                         VK_PIPELINE_BIND_POINT_GRAPHICS,
                                         0,
                                         nullptr,
                                         1,
                                         &colorAttachments,
                                         nullptr,
                                         nullptr,
                                         0,
                                         nullptr);

        createInfo.setSubpassDependency(VK_SUBPASS_EXTERNAL, 0, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0,
                                        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT, 0);

        VkRenderPassCreateInfo passCreateInfo = {VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
        passCreateInfo.attachmentCount = 1;
        passCreateInfo.pAttachments = &createInfo.getAttachmentDescription()[0];
        passCreateInfo.subpassCount = 1;
        passCreateInfo.pSubpasses = createInfo.getSubpassDescription();
        passCreateInfo.dependencyCount = 1;
        passCreateInfo.pDependencies = createInfo.getSubpassDependency();

        VK_CHECK(vkCreateRenderPass(device, &passCreateInfo, nullptr, &mRenderpass), "Can not create renderpass!");

        return mRenderpass;
    }
}