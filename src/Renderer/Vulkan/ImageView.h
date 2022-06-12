//
// Created by KSTOYAN2 on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../../Core/Core.h"
#include "RendererData.h"

namespace FikoEngine{
    std::vector<VkImageView> CreateImageViews(RendererDataAPI& rendererData);
}