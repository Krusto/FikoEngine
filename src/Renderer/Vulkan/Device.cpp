//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Memory.h"
#include "Device.h"
#include "Queue.h"
namespace FikoEngine {
    VkDevice CreateDevice(VkPhysicalDevice physicalDevice,u32& queueFamilyIndex, std::vector<const char *> &extensions) {
        VkDevice device{};
        VkDeviceCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDeviceQueueCreateInfo queueCreateInfo{.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
        queueCreateInfo.queueCount = 1;

        queueFamilyIndex = SelectQueueFamily(physicalDevice);
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        const float priorities[] = {1};
        queueCreateInfo.pQueuePriorities = priorities;

        createInfo.queueCreateInfoCount = 1;
        createInfo.pQueueCreateInfos = &queueCreateInfo;

        VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));
        LOG("Device created successfully!");

        return device;
    }
}