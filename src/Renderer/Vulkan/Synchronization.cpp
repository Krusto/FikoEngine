//
// Created by Stoyanov, Krusto (K.S.) on 6/22/2022.
//
#include "../../Core/Core.h"
#include "Synchronization.h"
#include "Memory.h"
#include "VulkanContext.h"

namespace FikoEngine{
    std::vector<VkSemaphore> CreateSemaphores(RendererDataAPI*  rendererData, u32 count){
        std::vector<VkSemaphore> semaphores(count);

        for (int i = 0; i < count; ++i) {
            VkSemaphoreCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
            VK_CHECK(vkCreateSemaphore(rendererData->device,&createInfo,nullptr,&semaphores[i]));
            LOG_INFO("Created Semaphore!");
        }

        return semaphores;
    }
    std::vector<VkFence> CreateFences(RendererDataAPI*  rendererData,u32 count){
        std::vector<VkFence> fences(count);

        for (int i = 0; i < count; ++i) {
            VkFenceCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
            createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            VK_CHECK(vkCreateFence(rendererData->device,&createInfo,nullptr,&fences[i]));
            LOG_INFO("Created Fence!");
        }

        return fences;
    }
    void WaitFence(std::vector<VkFence>& fences,u32 index){
        vkWaitForFences(VulkanContext::s_RendererData.device, 1, &fences[index], VK_TRUE, UINT64_MAX);
    }
    void ResetFence(std::vector<VkFence>& fences,u32 index){
        vkResetFences(VulkanContext::s_RendererData.device, 1, &fences[index]);
    }
}