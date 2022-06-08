//
// Created by KSTOYAN2 on 6/7/2022.
//
#include "Instance.h"

namespace FikoEngine{
    VkInstance CreateInstance(ApplicationSpec applicationSpec){
        VkInstance instance;
        VkInstanceCreateInfo createInfo{};
        VkApplicationInfo applicationInfo{};
        applicationInfo.apiVersion = VK_API_VERSION_1_3;
        applicationInfo.applicationVersion = VK_MAKE_VERSION(applicationSpec.AppVersion.Major,
                                                             applicationSpec.AppVersion.Minor,
                                                             applicationSpec.AppVersion.Patch);
        applicationInfo.engineVersion = VK_VERSION_1_0;
        applicationInfo.pApplicationName = applicationSpec.ApplicationName.data();
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        createInfo.pApplicationInfo = &applicationInfo;

#ifdef _DEBUG
        createInfo.enabledLayerCount = 1;
        const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
        createInfo.ppEnabledLayerNames = layers;
        const char *extensions[] = {"VK_EXT_debug_utils", "VK_EXT_debug_report"};
        createInfo.enabledExtensionCount = 2;
        createInfo.ppEnabledExtensionNames = extensions;
#else
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
#endif

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        if (VK_SUCCESS != vkCreateInstance(&createInfo, nullptr, &instance)) {
            exit(-1);
        }
        return instance;
    }
}