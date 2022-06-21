//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "PhysicalDevice.h"
#include "../../Core/Core.h"
#include <iostream>

namespace FikoEngine {
VkPhysicalDevice SelectPhysicalDevice(RendererDataAPI& rendererData) {

    u32 count{};
    vkEnumeratePhysicalDevices(rendererData.instance, &count, nullptr);
    std::vector<VkPhysicalDevice> devices(count);
    vkEnumeratePhysicalDevices(rendererData.instance, &count, devices.data());
    VkPhysicalDevice selectedDevice = devices[0];
    for (auto device: devices) {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        LOG_INFO("Checking " + std::string(properties.deviceName));
        if (VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU == properties.deviceType)
            selectedDevice = device;
    }

    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(selectedDevice, &properties);
    LOG("Selected "+std::string(properties.deviceName));
    return selectedDevice;
}
}