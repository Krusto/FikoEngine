#pragma once

#include "RenderCommand.h"

namespace FikoEngine {

    class Renderer {
    public:
        static void Init(FikoEngine::Window window);
        static void Begin();
        static void End();

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };


}
