//
// Created by KSTOYAN2 on 6/7/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../../Application/ApplicationSpec.h"

namespace FikoEngine{
///Function which creates api instance
    VkInstance CreateInstance(ApplicationSpec applicationSpec);
}