//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../../Core/Core.h"

namespace FikoEngine{
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct SwapChainSpec{
        uint32_t                         minImageCount;
        VkFormat                         imageFormat;
        VkColorSpaceKHR                  imageColorSpace;
        VkExtent2D                       imageExtent;
        uint32_t                         imageArrayLayers;
        VkImageUsageFlags                imageUsage;
        VkSharingMode                    imageSharingMode;
        VkSurfaceTransformFlagBitsKHR    preTransform;
        VkCompositeAlphaFlagBitsKHR      compositeAlpha;
        VkPresentModeKHR                 presentMode;
        VkBool32                         clipped = VK_TRUE;
        SwapChainSupportDetails details;
    };
}