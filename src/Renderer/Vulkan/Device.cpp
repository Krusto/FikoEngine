//
// Created by KSTOYAN2 on 6/7/2022.
//
#include "../Memory.h"
#include "Device.h"
#include "Queue.h"
namespace FikoEngine {
    VkDevice CreateDevice(RendererDataAPI& rendererData, std::vector<const char *> &extensions) {
        VkDevice device{};
        VkDeviceCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDeviceQueueCreateInfo queueCreateInfo{.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.queueFamilyIndex = SelectQueueFamily(rendererData);
        const f32 priorities[] = {1};
        queueCreateInfo.pQueuePriorities = priorities;

        createInfo.queueCreateInfoCount = 1;
        createInfo.pQueueCreateInfos = &queueCreateInfo;

        VK_CHECK(vkCreateDevice(rendererData.physicalDevice, &createInfo, CreatePAllocator("Device"), &device));
        LOG("Device created successfully!");

        return device;
    }
}