//
// Created by KSTOYAN2 on 6/7/2022.
//
#pragma once
#include "../../Core/Core.h"
#include <vulkan/vulkan.h>

namespace FikoEngine{
    VkDevice CreateDevice(VkInstance instance,VkPhysicalDevice physicalDevice,std::vector<const char*>& extensions);
}