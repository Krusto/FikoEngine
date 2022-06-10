//
// Created by KSTOYAN2 on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include <lwlog.h>
#include "RendererAPI.h"
#include "Vulkan/Instance.h"
#include "Vulkan/PhysicalDevice.h"
#include "Vulkan/Device.h"
#include "Platform.h"
#include "Window.h"
#include "Vulkan/Swapchain.h"

namespace FikoEngine {
    static QueueFamilyIndices s_RendererQueueFamilyIndices;

    void RendererAPI::Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec) {
        VkInstance instance = CreateInstance(applicationSpec);
        VkPhysicalDevice physicalDevice = SelectPhysicalDevice(instance);
        VkDevice device = CreateDevice(instance,physicalDevice,rendererSpec.extensions);
        VkSurfaceKHR surface = applicationSpec.window->CreateSurface(instance);

        LOG("Renderer initialized!");

        vkDestroySurfaceKHR(instance,surface,nullptr);
        vkDestroyDevice(device,nullptr);
        vkDestroyInstance(instance,nullptr);
    }
}