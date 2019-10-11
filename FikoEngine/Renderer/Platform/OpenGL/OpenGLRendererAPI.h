//
// Created by krusto on 30.08.19 г..
//

#ifndef FIKOENGINE_VULKANRENDERERAPI_H
#define FIKOENGINE_VULKANRENDERERAPI_H

#include "../../RendererAPI.h"
#include "OpenGLCore.h"

namespace FikoEngine {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void Init(FikoEngine::Window window) override;
        virtual void Begin() override;
        virtual void End() override;
        virtual void Clear() override;

    private:
        OpenGLRenderer::OpenGLCore mCore;
    };

}
#endif //FIKOENGINE_VULKANRENDERERAPI_H
