//
// Created by krusto on 30.08.19 г..
//

#ifndef FIKOENGINE_VULKANRENDERERAPI_H
#define FIKOENGINE_VULKANRENDERERAPI_H

#include "../../RendererAPI.h"
#include "VulkanCore.h"

namespace FikoEngine {
    class VulkanRendererAPI : public RendererAPI {
        virtual void Init(FikoEngine::Window window) override;

        virtual void Clear() override;

    private:
        VulkanRenderer::VulkanCore mCore;
    };

}
#endif //FIKOENGINE_VULKANRENDERERAPI_H
