//
// Created by Stoyanov, Krusto (K.S.) on 6/22/2022.
//
#include <Core/Core.h>
#include "Synchronization.h"
#include "Memory.h"
#include "VulkanRenderer.h"

namespace FikoEngine{
    std::vector<VkSemaphore> CreateSemaphores(RendererDataAPI*  rendererData, uint32_t count){
        std::vector<VkSemaphore> semaphores(count);

        for (uint32_t i = 0; i < count; ++i) {
            VkSemaphoreCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
            VK_CHECK(vkCreateSemaphore(rendererData->device,&createInfo,nullptr,&semaphores[i]));
        }

        return semaphores;
    }
    std::vector<VkFence> CreateFences(RendererDataAPI*  rendererData,uint32_t count){
        std::vector<VkFence> fences(count);

        for (uint32_t i = 0; i < count; ++i) {
            VkFenceCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
            createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            VK_CHECK(vkCreateFence(rendererData->device,&createInfo,nullptr,&fences[i]));
        }

        return fences;
    }
    void WaitFence(std::vector<VkFence>& fences,uint32_t index){
        vkWaitForFences(VulkanRenderer::s_RendererData.device, 1, &fences[index], VK_TRUE, UINT64_MAX);
    }
    void ResetFence(std::vector<VkFence>& fences,uint32_t index){
        vkResetFences(VulkanRenderer::s_RendererData.device, 1, &fences[index]);
    }
}