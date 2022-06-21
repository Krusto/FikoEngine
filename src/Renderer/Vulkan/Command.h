//
// Created by Stoyanov, Krusto (K.S.) on 6/20/2022.
//
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{
    VkCommandPool CreateCommandPool(RendererDataAPI& rendererData);
    VkCommandBuffer CreateCommandBuffer(RendererDataAPI& rendererData);
    std::vector<VkCommandBuffer> CreateCommandBuffers(RendererDataAPI& rendererData,u32 count = 1);

    void RecordCommandBuffer(RendererDataAPI& rendererData,u32 index = {});
    void EndCommandBuffer(RendererDataAPI& rendererData,u32 index = {});
}