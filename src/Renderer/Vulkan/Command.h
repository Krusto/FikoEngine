//
// Created by Stoyanov, Krusto (K.S.) on 6/20/2022.
//
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{
    VkCommandPool CreateCommandPool(VkDevice device, u32 queueFamilyIndex);
    VkCommandBuffer CreateCommandBuffer(VkDevice device, VkCommandPool commandPool);

    std::vector<VkCommandBuffer> CreateCommandBuffers(VkDevice device,VkCommandPool commandPool,u32 count = 1);

    void BeginCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,u32 index = {});
    void EndCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,u32 index = {});
    void ResetCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,u32 index = {});
}