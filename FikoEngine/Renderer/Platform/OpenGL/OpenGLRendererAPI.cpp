//
// Created by krusto on 30.08.19 г..
//

#include "OpenGLRendererAPI.h"
namespace FikoEngine {
    void FikoEngine::OpenGLRendererAPI::Init(FikoEngine::Window window) {
        mCore.Init(window);
    }

    void FikoEngine::OpenGLRendererAPI::Begin() {
        mCore.Begin();
    }

    void FikoEngine::OpenGLRendererAPI::End() {
        mCore.End();
    }

    void FikoEngine::OpenGLRendererAPI::Clear() {

    }
}