//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//

#include "ImageView.h"
#include "Memory.h"

namespace FikoEngine{
    std::vector<VkImageView> CreateImageViews(VkDevice device,Swapchain* swapchain){
        std::vector<VkImageView> imageViews(swapchain->GetSwapchainSpec().minImageCount);
        swapchain->FramesCount = swapchain->GetSwapchainSpec().minImageCount;
        for (u32 i = 0; i < imageViews.size(); ++i) {
            VkImageViewCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.image = swapchain->GetImages()[i];
            createInfo.format = swapchain->GetSwapchainSpec().imageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            VK_CHECK(vkCreateImageView(device,&createInfo,nullptr,&imageViews[i]));
        }
        return imageViews;
    }

}