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
            inline VulkanCore() = default;

            void Init();

            ~VulkanCore();

        private:

            VulkanCreateInfos createInfo;


            VkResult mCreateInstance();
            VkResult mSelectPhysicalDevice(VkPhysicalDeviceType physicalDeviceType);
            VkResult mSelectQueueFamilyIndex();
            VkResult mCreateDevice();
            VkResult mCreateDebugCallback();

            VkPhysicalDevice mPhysicalDevice;
            VkInstance mInstance;
            VkDevice mDevice;
            VkDebugReportCallbackEXT mDebugReportCallback;

            VkCommandPool mCommandPool;
            VkCommandBuffer mCommandBuffer;

            uint32_t mQueueFamilyIndex;


        };
    }

#endif //FIKOENGINE_VULKANCORE_H
