//
// Created by krusto on 9/17/19.
//

#ifndef FIKOENGINE_QUEUE_H
#define FIKOENGINE_QUEUE_H

#include <vulkan/vulkan.h>

namespace FikoEngine::VulkanRenderer {
    class QueueFamilyIndex{
    public:
        static uint32_t Select(VkPhysicalDevice physicalDevice, VkQueueFlags flags);
    };
}

#endif //FIKOENGINE_QUEUE_H
