//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include "Window.h"
#include "../Core/Core.h"

namespace FikoEngine {

///Struct which holds renderer specification
struct RendererSpec {
public:
    Extent2D SurfaceSize;
    std::vector<const char*> extensions;
};
class Renderer {
public:
    Renderer() = default;
///Function which inits the whole renderer
    void Init(RendererSpec rendererSpec,ApplicationSpec applicationSpec);
    void Draw();
    void Destroy();
    void ResizeFramebuffer(Extent2D size);
    void Update();
private:
    RendererSpec m_RendererSpec;
};
}