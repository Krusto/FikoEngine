//
// Created by KSTOYAN2 on 6/7/2022.
//
#pragma once
#include <vulkan/vulkan.h>

namespace FikoEngine{
///Function which selects the correct physical device
    VkPhysicalDevice SelectPhysicalDevice(VkInstance instance);
}