#include "AllocationManger.h"
#include "VulkanUtilities.h"

namespace FikoEngine::VulkanRenderer {
    VkCommandPool CommandPool::createCommandPool(VkDevice device, uint32_t queueFamilyIndex) {
        VkCommandPool commandPool;
        createInfo.setCommandPoolCreateInfo(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,queueFamilyIndex);

        VK_CHECK(vkCreateCommandPool(device,createInfo.getCommandPoolCreateInfo(),nullptr,&commandPool),"Can not create command pool!");

        return commandPool;
    }

    void CommandPool::Reset(VkDevice device, VkCommandPool commandPool) {
        VK_CHECK(vkResetCommandPool(device,commandPool,VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT),"Can not reset command pool!");
    }

    void CommandBuffer::allocateCommandBuffer(VkDevice device, VkCommandPool commandPool,uint32_t count) {
        commandBuffers.resize(count);
        createInfo.setCommandBufferAllocateInfo(commandPool,VK_COMMAND_BUFFER_LEVEL_PRIMARY,commandBuffers.size());

        VK_CHECK(vkAllocateCommandBuffers(device,createInfo.getCommandBufferAllocateInfo(),commandBuffers.data()),"Can not allocate command buffer!");
    }

    void CommandBuffer::Begin(uint32_t commandBufferIndex) {
        VkCommandBufferBeginInfo beginInfo={
                                     VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                     NULL,
                                      VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
                              0};

        VK_CHECK(vkBeginCommandBuffer(commandBuffers[commandBufferIndex], &beginInfo));
    }

    void CommandBuffer::End(uint32_t commandBufferIndex) {
        vkEndCommandBuffer(commandBuffers[commandBufferIndex]);
    }
}