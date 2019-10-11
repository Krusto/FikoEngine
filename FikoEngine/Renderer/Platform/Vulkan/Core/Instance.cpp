//
// Created by krusto on 9/16/19.
//

#include "Instance.h"
#include "../VulkanUtilities.h"

#include <vector>
#include <GLFW/glfw3.h>

namespace FikoEngine::VulkanRenderer {
    VkInstance Instance::Init(bool debugEnable) {
        std::vector<const char *> Layers;
        uint32_t glfwExtensionCount = 0;
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> glfwExtensions(&glfwGetRequiredInstanceExtensions(&glfwExtensionCount)[0],
                                                 &glfwGetRequiredInstanceExtensions(
                                                         &glfwExtensionCount)[glfwExtensionCount]);
        if(debugEnable) {
            Layers.push_back("VK_LAYER_KHRONOS_validation");
            glfwExtensions.insert(glfwExtensions.begin(), VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        }

#if defined(_LINUX)
        glfwExtensions.emplace_back("VK_KHR_xlib_surface");
#endif
#if defined(_WIN32)
        glfwExtensions.emplace_back("VK_KHR_win32_surface");
#endif

        createInfo.setInstanceAttr(&Layers, &glfwExtensions);

        VkInstance instance;
        VK_CHECK(vkCreateInstance(createInfo.getVkInstance(), nullptr, &instance),"Can not create instance");
        return instance;
    }
}