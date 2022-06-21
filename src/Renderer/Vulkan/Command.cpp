//
// Created by Stoyanov, Krusto (K.S.) on 6/20/2022.
//
#include "Command.h"
#include "../../Core/Core.h"
#include "Memory.h"
namespace FikoEngine {
    VkCommandPool CreateCommandPool(RendererDataAPI& rendererData){
        VkCommandPool pool{};
        VkCommandPoolCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
        createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        createInfo.queueFamilyIndex = rendererData.queueFamilyIndex;

        VK_CHECK(vkCreateCommandPool(rendererData.device,&createInfo,CreatePAllocator("CommandPool"),&pool));
        LOG_INFO("Created Command Pool");
        return pool;
    }
    VkCommandBuffer CreateCommandBuffer(RendererDataAPI& rendererData){
        VkCommandBuffer buffer{};
        VkCommandBufferAllocateInfo createInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
        createInfo.commandPool = rendererData.commandPool;
        createInfo.commandBufferCount = 1;
        createInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        VK_CHECK(vkAllocateCommandBuffers(rendererData.device,&createInfo,&buffer));
        return buffer;
    }
    std::vector<VkCommandBuffer> CreateCommandBuffers(RendererDataAPI& rendererData,u32 count){
        std::vector<VkCommandBuffer> buffers(count);
        for (auto &buffer: buffers)
            buffer = CreateCommandBuffer(rendererData);
        return buffers;
    }
    void BeginCommandBuffer(RendererDataAPI& rendererData,u32 index){
        VkCommandBufferBeginInfo beginInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
        VK_CHECK(vkBeginCommandBuffer(rendererData.commandBuffers[index],&beginInfo));
    }
    void EndCommandBuffer(RendererDataAPI& rendererData,u32 index){
        VK_CHECK(vkEndCommandBuffer(rendererData.commandBuffers[index]));
    }

}