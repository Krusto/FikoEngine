//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../../Core/Core.h"
#include "RendererData.h"
namespace FikoEngine{
    VkFramebuffer CreateFramebuffer(RendererDataAPI*  rendererData, u32 index);
    std::vector<VkFramebuffer> CreateFramebuffers(RendererDataAPI*  rendererData);
}