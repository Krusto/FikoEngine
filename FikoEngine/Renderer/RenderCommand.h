#pragma once

#include "RendererAPI.h"

namespace FikoEngine {

    class RenderCommand {
    public:
        inline static void Init(FikoEngine::Window window) {
            s_RendererAPI->Init(window);
        }
        inline static void Begin(){
            s_RendererAPI->Begin();
        }
        inline static void End(){
            s_RendererAPI->End();
        }
    private:
        static RendererAPI *s_RendererAPI;
    };

}
