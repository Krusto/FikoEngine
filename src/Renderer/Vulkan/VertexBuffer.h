//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once

#include <vulkan/vulkan.h>
#include "Buffer.h"
#include "RendererData.h"
#include "../VertexLayout.h"
#include "../../Core/Core.h"
#include "../Vertex.h"

namespace FikoEngine {
    Buffer CreateVertexBuffer(RendererDataAPI* rendererData,Vertex* data,VertexLayout vertexLayout,u32 vertexCount);



}