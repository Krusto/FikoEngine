//
// Created by Stoyanov, Krusto (K.S.) on 6/22/2022.
//
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{

    std::vector<VkSemaphore> CreateSemaphores(RendererDataAPI& rendererData,u32 count = 1);
    std::vector<VkFence> CreateFences(RendererDataAPI& rendererData,u32 count = 1);
}