//
// Created by krusto on 10/9/19.
//

#ifndef FIKOENGINE_RENDERPASS_H
#define FIKOENGINE_RENDERPASS_H

#include <vulkan/vulkan.h>
namespace FikoEngine::VulkanRenderer {
    class RenderPass {
    public:
        static VkRenderPass CreateRenderpass(VkDevice device, VkSurfaceFormatKHR surfaceFormat);
    };
}

#endif //FIKOENGINE_RENDERPASS_H
