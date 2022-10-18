#pragma once
#include "../Core/Core.h"
#include "Viewport.h"

namespace FikoEngine{
    ///Struct which holds renderer specification
    struct RendererSpecAPI {
        ViewportSize SurfaceSize;
        std::vector<const char*> extensions;
    };
}