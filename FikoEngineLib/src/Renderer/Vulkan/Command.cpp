//
// Created by Stoyanov, Krusto (K.S.) on 6/20/2022.
//
#include "Command.h"
#include "../../Core/Core.h"
#include "Memory.h"
namespace FikoEngine {
    VkCommandPool CreateCommandPool(VkDevice device, uint32_t queueFamilyIndex) {
        VkCommandPool pool{};
        VkCommandPoolCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
        createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        createInfo.queueFamilyIndex = queueFamilyIndex;

        VK_CHECK(vkCreateCommandPool(device,&createInfo,nullptr,&pool));
        return pool;
    }
    VkCommandBuffer CreateCommandBuffer(VkDevice device, VkCommandPool commandPool) {
        VkCommandBuffer buffer{};
        VkCommandBufferAllocateInfo createInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
        createInfo.commandPool = commandPool;
        createInfo.commandBufferCount = 1;
        createInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        VK_CHECK(vkAllocateCommandBuffers(device,&createInfo,&buffer));
        return buffer;
    }

    std::vector<VkCommandBuffer> CreateCommandBuffers(VkDevice device,VkCommandPool commandPool,uint32_t count){
        std::vector<VkCommandBuffer> buffers(count);
        for (auto &buffer: buffers)
            buffer = CreateCommandBuffer(device,commandPool);
        return buffers;
    }

    void BeginCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,uint32_t index){
        VkCommandBufferBeginInfo beginInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        VK_CHECK(vkBeginCommandBuffer(commandBuffers[index],&beginInfo));
    }
    void EndCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,uint32_t index){
        VK_CHECK(vkEndCommandBuffer(commandBuffers[index]));
    }
    void ResetCommandBuffer(std::vector<VkCommandBuffer> commandBuffers,uint32_t index){
        VK_CHECK(vkResetCommandBuffer(commandBuffers[index], /*VkCommandBufferResetFlagBits*/ 0));
    }




}