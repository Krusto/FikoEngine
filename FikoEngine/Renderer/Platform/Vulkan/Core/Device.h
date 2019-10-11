//
// Created by krusto on 9/17/19.
//

#ifndef FIKOENGINE_DEVICE_H
#define FIKOENGINE_DEVICE_H


#include <vulkan/vulkan.h>
#include <vector>

namespace FikoEngine::VulkanRenderer {
    class PhysicalDevice{
    public:
        static VkPhysicalDevice Select(VkPhysicalDeviceType type,std::vector<VkPhysicalDevice> devices);
        static std::vector<VkPhysicalDevice> Enumerate(VkInstance instance);
    };

    class LogicalDevice {
    public:
        static VkDevice Create(uint32_t QueueFamilyIndex,VkPhysicalDevice physicalDevice);
    };

}
#endif //FIKOENGINE_DEVICE_H
