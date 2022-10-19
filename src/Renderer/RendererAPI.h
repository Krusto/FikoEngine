//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include <glm/vec4.hpp>
#include "../Core/Core.h"
#include "Window.h"
#include "RendererSpec.h"
#include "Viewport.h"

namespace FikoEngine {

///Class interfacing the renderer with the api
class RendererAPI {
public:
///Function which inits the renderer api
    static void Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec);
    static void Draw();
    static void Destroy();
    static void ResizeFramebuffer(ViewportSize size);

    enum API{
        None,
        OpenGL,
        Vulkan
    };

    static RendererAPI::API Current(){return RendererAPI::s_api;}

    static void ClearColor(glm::vec4 color = {0.0f,0.0f,0.0f,1.0f});

    inline static API s_api = API::Vulkan;
private:

};
}