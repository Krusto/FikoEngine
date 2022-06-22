//
// Created by Stoyanov, Krusto (K.S.) on 6/12/2022.
//
#include <vulkan/vulkan.h>
#include "../../Core/Core.h"
#include "RendererData.h"

namespace FikoEngine{
    VkRenderPass CreateRenderPass(RendererDataAPI*  rendererData);
    void BeginRenderPass(RendererDataAPI*  rendererData, u32 index = {});
    void EndRenderPass(RendererDataAPI*  rendererData, u32 index = {});
}