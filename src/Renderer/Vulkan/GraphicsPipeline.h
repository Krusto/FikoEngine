//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"
namespace FikoEngine{
    VkPipeline CreateGraphicsPipeline(RendererDataAPI& rendererData,const char* shaderPath);
    void BindGraphicsPipeline(RendererDataAPI& rendererData,u32 imageIndex = {});
    void GraphicsPipelineDraw(RendererDataAPI& rendererData,u32 imageIndex = {});
}