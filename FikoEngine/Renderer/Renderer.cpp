#include "Renderer.h"

namespace FikoEngine {

    void Renderer::Init(FikoEngine::Window window) {
        RenderCommand::Init(window);
    }

    void Renderer::Begin() {
        RenderCommand::Begin();
    }

    void Renderer::End() {
        RenderCommand::End();
    }

}