//
// Created by Stoyanov, Krusto (K.S.) on 6/22/2022.
//
#include "../../Core/Core.h"
#include "Synchronization.h"
#include "Memory.h"

namespace FikoEngine{
    std::vector<VkSemaphore> CreateSemaphores(RendererDataAPI& rendererData, u32 count){
        std::vector<VkSemaphore> semaphores(count);

        for (int i = 0; i < count; ++i) {
            VkSemaphoreCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
            VK_CHECK(vkCreateSemaphore(rendererData.device,&createInfo,CreatePAllocator("Semaphore"),&semaphores[i]));
            LOG_INFO("Created Semaphore!");
        }

        return semaphores;
    }
    std::vector<VkFence> CreateFences(RendererDataAPI& rendererData,u32 count){
        std::vector<VkFence> fences(count);

        for (int i = 0; i < count; ++i) {
            VkFenceCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
            createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            VK_CHECK(vkCreateFence(rendererData.device,&createInfo,CreatePAllocator("Fence"),&fences[i]));
            LOG_INFO("Created Semaphore!");
        }

        return fences;
    }
}