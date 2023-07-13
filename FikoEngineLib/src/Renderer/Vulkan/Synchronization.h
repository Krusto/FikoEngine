//
// Created by Stoyanov, Krusto (K.S.) on 6/22/2022.
//
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{

    std::vector<VkSemaphore> CreateSemaphores(RendererDataAPI*  rendererData,uint32_t count = 1);
    std::vector<VkFence> CreateFences(RendererDataAPI*  rendererData,uint32_t count = 1);

    void WaitFence(std::vector<VkFence>& fences,uint32_t index = {});
    void ResetFence(std::vector<VkFence>& fences,uint32_t index = {});
}