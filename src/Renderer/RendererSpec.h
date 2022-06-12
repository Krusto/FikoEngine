#pragma once
#include "../Core/Core.h"
namespace FikoEngine{
    ///Struct which holds renderer specification
    struct RendererSpecAPI {
        u32 SurfaceWidth;
        u32 SurfaceHeight;
        std::vector<const char*> extensions;
    };
}