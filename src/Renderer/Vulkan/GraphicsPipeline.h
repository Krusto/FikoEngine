//
// Created by KSTOYAN2 on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"
namespace FikoEngine{
    VkPipeline CreateGraphicsPipeline(RendererDataAPI& rendererData,const char* shaderPath);
}