//
// Created by KSTOYAN2 on 6/7/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../../Core/Core.h"

namespace FikoEngine{
    struct QueueFamilyIndices{
        std::optional<u32> graphicsFamily;
        std::optional<u32> presentFamily;
    };
    u32 SelectQueueFamily(VkPhysicalDevice physicalDevice);
}