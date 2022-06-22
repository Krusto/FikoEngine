//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include "../Core/Core.h"
#include "Vulkan/Queue.h"
#include "Window.h"
#include "RendererSpec.h"

namespace FikoEngine {


///Class interfacing the renderer with the api
class RendererAPI {
public:
///Function which inits the renderer api
    static void Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec);
    static void Draw();
    static void Destroy();
    static void ResizeFramebuffer(Extent2D size);
private:
    static QueueFamilyIndices s_RendererQueueFamilyIndices;
};
}