//
// Created by Stoyanov, Krusto (K.S.) on 6/20/2022.
//
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{
    VkCommandPool CreateCommandPool(RendererDataAPI*  rendererData);
    VkCommandBuffer CreateCommandBuffer(RendererDataAPI*  rendererData);
    VkCommandBuffer CreateCommandBuffer(VkDevice device,VkCommandPool commandPool);

    std::vector<VkCommandBuffer> CreateCommandBuffers(RendererDataAPI*  rendererData,u32 count = 1);

    void BeginCommandBuffer(VkCommandBuffer buffer);
    void EndCommandBuffer(VkCommandBuffer buffer);
    void ResetCommandBuffer(VkCommandBuffer buffer);
    void BeginCommandBuffer(RendererDataAPI*  rendererData,u32 index = {});
    void EndCommandBuffer(RendererDataAPI*  rendererData,u32 index = {});
    void ResetCommandBuffer(RendererDataAPI*  rendererData,u32 index = {});
}