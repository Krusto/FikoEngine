//
// Created by krusto on 9/17/19.
//

#include <bits/exception.h>
#include <vector>
#include "Queue.h"
#include "../VulkanUtilities.h"

uint32_t FikoEngine::VulkanRenderer::QueueFamilyIndex::Select(VkPhysicalDevice physicalDevice, VkQueueFlags flags) {
    uint32_t size;
    try {
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &size, nullptr);
    } catch (std::exception &e) {
        VK_CHECK(VkResult::VK_TIMEOUT, "Can not retrieve queue family count");
        return -1;
    }
    std::vector<VkQueueFamilyProperties> props(size);
    try {
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &size, props.data());
    } catch (std::exception &e) {
        VK_CHECK(VkResult::VK_TIMEOUT, "Can not retrieve queue family properties");
        return -1;
    }

    for (uint32_t i = 0; i < size; ++i) {
        VkQueueFlags currentFlag = props[i].queueFlags;
        if (currentFlag & flags) {
            return i;
        }
    }
    return -1;
}
