//
// Created by Stoyanov, Krusto (K.S.) on 6/25/2022.
//
#pragma once

#include <vulkan/vulkan.h>
#include "Buffer.h"
#include "RendererData.h"
#include "../VertexLayout.h"
#include "../../Core/Core.h"

namespace FikoEngine {
    Buffer CreateIndexBuffer(RendererDataAPI* rendererData,u32* data,u32 count);



}