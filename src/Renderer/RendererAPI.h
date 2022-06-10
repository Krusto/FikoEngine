//
// Created by KSTOYAN2 on 6/7/2022.
//
#pragma once

#include "../Core/Core.h"
#include "Vulkan/Queue.h"
#include "Window.h"

namespace FikoEngine {

///Struct which holds renderer specification
struct RendererSpecAPI {
    u32 SurfaceWidth;
    u32 SurfaceHeight;
    std::vector<const char*> extensions;
};
///Class interfacing the renderer with the api
class RendererAPI {
public:
///Function which inits the renderer api
    static void Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec);
private:
    static QueueFamilyIndices s_RendererQueueFamilyIndices;
};
}