//
// Created by krusto on 9/17/19.
//

#include "Device.h"
#include "../VulkanUtilities.h"

#include <string>

VkPhysicalDevice FikoEngine::VulkanRenderer::PhysicalDevice::Select(VkPhysicalDeviceType type,std::vector<VkPhysicalDevice> devices) {
    VkPhysicalDevice device;
    for (int i = 0; i < devices.size(); ++i) {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(devices[i], &props);
        if (props.deviceType == type) {
            device = devices[i];
            FIKO_CORE_INFO(
                    "Selected Graphical Proccessing Unit with name : " + std::string(props.deviceName) + "\n");
            return device;
        }
    }
    if(devices.size() > 0){
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(devices[0],&props);
        device = Select(props.deviceType,devices);

    }else{
        FIKO_CORE_ERROR("Physical device count is zero!");

    }
    return device;
}

std::vector<VkPhysicalDevice> FikoEngine::VulkanRenderer::PhysicalDevice::Enumerate(VkInstance instance) {
    uint32_t deviceCount;

    VK_CHECK(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr), "Can not enumerate physical devices!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    VK_CHECK(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()),
             "Can not enumerate physical devices!");


    return devices;
}

VkDevice FikoEngine::VulkanRenderer::LogicalDevice::Create(uint32_t QueueFamilyIndex, VkPhysicalDevice physicalDevice) {
    createInfo.setQueueFamilyAttr(QueueFamilyIndex);
    const float priorities = {0.00};
    createInfo.setVkQueueCreateInfo(0, QueueFamilyIndex, 1, &priorities);

    std::vector<const char*> deviceExtensions;
    deviceExtensions.emplace_back("VK_KHR_swapchain");
    deviceExtensions.emplace_back("VK_KHR_maintenance2");
    deviceExtensions.emplace_back("VK_KHR_image_format_list");
    deviceExtensions.emplace_back("VK_KHR_swapchain_mutable_format");

    createInfo.setVkDeviceCreateInfo(1, createInfo.getDeviceQueueCreateInfo(0),deviceExtensions.size(), deviceExtensions.data(), nullptr);

    VkDevice device;
    VK_CHECK( vkCreateDevice(physicalDevice, createInfo.getDeviceCreateInfo(), nullptr,&device),"Can not create device!");
    return device;
}
