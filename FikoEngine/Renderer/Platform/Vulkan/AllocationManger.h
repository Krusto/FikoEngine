//
// Created by krusto on 1.09.19 г..
//

#ifndef FIKOENGINE_ALLOCATIONMANGER_H
#define FIKOENGINE_ALLOCATIONMANGER_H

#include <vulkan/vulkan.h>
#include <vector>

namespace FikoEngine::VulkanRenderer {
    class CommandPool{
    public:
        static VkCommandPool createCommandPool(VkDevice device, uint32_t queueFamilyIndex);
        static void Reset(VkDevice device,VkCommandPool commandPool);
    };

    class CommandBuffer{
    public:
        static std::vector<VkCommandBuffer> commandBuffers;
        static void allocateCommandBuffer(VkDevice device,VkCommandPool commandPool,uint32_t count = 1);
        static void Begin(uint32_t swapchainImageIndex);
        static void End(uint32_t commandBufferIndex);
    };
}


#endif //FIKOENGINE_ALLOCATIONMANGER_H
