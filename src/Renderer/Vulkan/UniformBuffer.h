//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#pragma once

#include <vulkan/vulkan.h>
#include "Buffer.h"
#include "RendererData.h"
#include "../UniformLayout.h"
#include "../../Core/Core.h"
#include "../Uniform.h"

namespace FikoEngine {
    Buffer CreateUniformBuffer(RendererDataAPI* rendererData,UniformLayout uniformLayout);
    std::vector<Buffer> CreateUniformBuffers(RendererDataAPI* rendererData,UniformLayout uniformLayout,u32 count = 0);

}