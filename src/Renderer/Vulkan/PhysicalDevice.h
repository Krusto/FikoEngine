//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"

namespace FikoEngine{
///Function which selects the correct physical device
    VkPhysicalDevice SelectPhysicalDevice(RendererDataAPI*  rendererData);
}