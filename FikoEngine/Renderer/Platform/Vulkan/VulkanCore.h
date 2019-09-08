//
// Created by krusto on 31.08.19 г..
//

#ifndef FIKOENGINE_VULKANCORE_H
#define FIKOENGINE_VULKANCORE_H
#include <iostream>
#include <vulkan/vulkan.h>
#include "VulkanCreateInfos.h"

namespace FikoEngine::VulkanRenderer {
        class VulkanCore {
        public:
            VulkanCore() = default;

            void Init();

            ~VulkanCore();

        private:

            VulkanCreateInfos createInfo;

            VkResult mCreateInstance();
            VkResult mSelectPhysicalDevice(VkPhysicalDeviceType physicalDeviceType);
            VkResult mSelectQueueFamilyIndex();
            VkResult mCreateDevice();
            VkResult mCreateDebugCallback();
            VkResult mGetSurface();
            VkResult mCreateSwapchainKHR();

            VkPhysicalDevice mPhysicalDevice;
            VkInstance mInstance;
            VkDevice mDevice;
            VkDebugReportCallbackEXT mDebugReportCallback;
            VkSurfaceKHR mSurface;
            uint32_t mQueueFamilyIndex;
        };
    }

#endif //FIKOENGINE_VULKANCORE_H
