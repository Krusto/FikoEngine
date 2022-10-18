//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <optional>
#include "../../Core/Core.h"
#include "RendererData.h"

namespace FikoEngine{
    struct QueueFamilyIndices{
        std::optional<u32> graphicsFamily;
        std::optional<u32> presentFamily;
    };
    u32 SelectQueueFamily(VkPhysicalDevice physicalDevice);
    void QueueSubmit(RendererDataAPI*  rendererData,u32 index = {});
    VkResult QueuePresent(RendererDataAPI*  rendererData,u32 imageIndex,u32 commandBufferIndex = {});
}