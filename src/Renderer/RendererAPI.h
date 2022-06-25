//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include "../Core/Core.h"
#include "Vulkan/Queue.h"
#include "Window.h"
#include "RendererSpec.h"

namespace FikoEngine 
{
class RendererAPI 
{
public:
    static void Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec);
    static void Draw();
    static void Destroy();
    static void ResizeFramebuffer(Extent2D size);
    static void Update();
    
private:
    static QueueFamilyIndices s_RendererQueueFamilyIndices;
};
}
