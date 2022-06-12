//
// Created by KSTOYAN2 on 6/7/2022.
//
#pragma once

#include "Window.h"
#include "../Core/Core.h"

namespace FikoEngine {

///Struct which holds renderer specification
struct RendererSpec {
public:
    u32 SurfaceWidth;
    u32 SurfaceHeight;
    std::vector<const char*> extensions;
};
class Renderer {
public:
    Renderer() = default;
///Function which inits the whole renderer
    void Init(RendererSpec rendererSpec,ApplicationSpec applicationSpec);

private:
    RendererSpec m_RendererSpec;
};
}