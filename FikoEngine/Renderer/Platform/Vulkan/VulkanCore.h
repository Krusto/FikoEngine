//
// Created by krusto on 31.08.19 г..
//

#ifndef FIKOENGINE_VULKANCORE_H
#define FIKOENGINE_VULKANCORE_H

#include <iostream>
#include <vulkan/vulkan.h>
#include "VulkanCreateInfos.h"
#include "../../../Window.h"

namespace FikoEngine::VulkanRenderer {
    class VulkanCore {
    public:
        VulkanCore() = default;

        void Init(FikoEngine::Window window);

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

        FikoEngine::Window* mWindow;
        VkPhysicalDevice mPhysicalDevice;
        VkInstance mInstance;
        VkDevice mDevice;
        VkDebugReportCallbackEXT mDebugReportCallback;
        VkSurfaceKHR mSurface;
        uint32_t mQueueFamilyIndex;
        VkSwapchainKHR mSwapchain;
    };
}

#endif //FIKOENGINE_VULKANCORE_H
