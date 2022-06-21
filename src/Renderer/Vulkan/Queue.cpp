//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Queue.h"
#include <vector>
namespace FikoEngine {
    u32 SelectQueueFamily(RendererDataAPI& rendererData) {
        u32 count{};
        vkGetPhysicalDeviceQueueFamilyProperties(rendererData.physicalDevice, &count, nullptr);
        std::vector<VkQueueFamilyProperties> properties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(rendererData.physicalDevice, &count, properties.data());
        u32 index{};
        for (const auto &property: properties) {
            if ((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT) & property.queueFlags)
                return index;
            index++;
        }
        return index;
    }

}