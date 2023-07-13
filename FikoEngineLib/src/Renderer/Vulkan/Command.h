//
// Created by Stoyanov, Krusto (K.S.) on 6/20/2022.
//
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{
    VkCommandPool CreateCommandPool(VkDevice device, uint32_t queueFamilyIndex);
    VkCommandBuffer CreateCommandBuffer(VkDevice device, VkCommandPool commandPool);

    std::vector<VkCommandBuffer> CreateCommandBuffers(VkDevice device,VkCommandPool commandPool,uint32_t count = 1);

    void BeginCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,uint32_t index = {});
    void EndCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,uint32_t index = {});
    void ResetCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,uint32_t index = {});
}