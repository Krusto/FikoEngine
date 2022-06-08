//
// Created by KSTOYAN2 on 6/7/2022.
//
#include "PhysicalDevice.h"
#include "../../Core/Core.h"
#include <iostream>

namespace FikoEngine {
VkPhysicalDevice SelectPhysicalDevice(VkInstance instance) {

    u32 count{};
    vkEnumeratePhysicalDevices(instance, &count, nullptr);
    std::vector<VkPhysicalDevice> devices(count);
    vkEnumeratePhysicalDevices(instance, &count, devices.data());
    VkPhysicalDevice selectedDevice = devices[0];
    for (auto device: devices) {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        if (VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU == properties.deviceType)
            selectedDevice = device;
    }

    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(selectedDevice, &properties);
    std::cout << "Selected " << properties.deviceName << std::flush;
    return selectedDevice;
}
}