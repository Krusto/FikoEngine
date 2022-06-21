//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"
#include "../../Core/Core.h"
namespace FikoEngine{
    std::vector<VkImage> GetSwapchainImages(RendererDataAPI& rendererData);
}