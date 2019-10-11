//
// Created by krusto on 9/16/19.
//

#ifndef FIKOENGINE_DEBUG_H
#define FIKOENGINE_DEBUG_H

#include <vulkan/vulkan.h>

namespace FikoEngine::VulkanRenderer {
    class Debug {
    public:
        static VkResult enableDebug(VkInstance instance,VkDebugReportCallbackEXT* dbgCallback);

    };
}

#endif //FIKOENGINE_DEBUG_H
