#pragma once

#include "../Window.h"

namespace FikoEngine {

    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL = 1, Vulkan = 2
        };

        virtual void Init(FikoEngine::Window window) = 0;

        virtual void Begin() = 0;
        virtual void End() = 0;

        virtual void Clear() = 0;

        inline static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };

}