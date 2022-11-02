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
    void QueueSubmit(VkQueue queue,std::vector<VkSemaphore>& imageAvailableSemaphores,std::vector<VkSemaphore>& renderFinishedSemaphores,std::vector<VkFence>& fences,u32 index = {});
    VkResult QueuePresent(VkQueue queue,Ref<Swapchain> swapchain,std::vector<VkSemaphore>& renderFinishedSemaphores,std::vector<VkFence>& fences, uint32_t imageIndex, uint32_t currentFrameIndex);
}