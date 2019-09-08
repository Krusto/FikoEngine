#pragma once

#include "RendererAPI.h"

namespace FikoEngine {

    class RenderCommand {
    public:
        inline static void Init(FikoEngine::Window window) {
            s_RendererAPI->Init(window);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };

}
