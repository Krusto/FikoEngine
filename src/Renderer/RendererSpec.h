#pragma once
#include "../Core/Core.h"

namespace FikoEngine
{
    ///Struct which holds renderer specification
    struct RendererSpecAPI 
    {
        Extent2D SurfaceSize;
        std::vector<const char*> extensions;
    };
}
