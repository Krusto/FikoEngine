//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"
#include "../../Core/Core.h"

namespace FikoEngine{
    VkDevice CreateDevice(VkPhysicalDevice physicalDevice,uint32_t& queueFamilyIndex,std::vector<const char*>& extensions);
}