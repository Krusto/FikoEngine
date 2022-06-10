//
// Created by KSTOYAN2 on 6/10/2022.
//
#pragma once
#include "../../Core/Core.h"
#include <vulkan/vulkan.h>
namespace FikoEngine{
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device,std::string_view extension);
    bool CheckSwapChainSupport(VkPhysicalDevice physicalDevice);
}