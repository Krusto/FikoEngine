//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Instance.h"
#include "Platform.h"
#include "Memory.h"
#include <vulkan/vulkan.h>
namespace FikoEngine{

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {
        if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            LOG_ERROR(std::string(pCallbackData->pMessage));
        }else if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            LOG_WARNING(std::string(pCallbackData->pMessage));
        }else{
            return VK_FALSE;
        }
        return VK_FALSE;
    }
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    VkInstance CreateInstance(RendererDataAPI*  rendererData,ApplicationSpec applicationSpec){
        VkInstance instance{};
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

        auto extensions = GetPlatformExtensions();
        extensions.push_back("VK_KHR_surface");
#ifdef _DEBUG
        createInfo.enabledLayerCount = 1;
        const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
        createInfo.ppEnabledLayerNames = layers;

        extensions.push_back("VK_EXT_debug_utils");
        extensions.push_back("VK_EXT_debug_report");
#else
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
#endif
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        VK_CHECK(vkCreateInstance(&createInfo,nullptr,&instance));
        LOG("Instance created successfully!");

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = debugCallback;
        debugCreateInfo.pUserData = nullptr; // Optional

        CreateDebugUtilsMessengerEXT(instance,&debugCreateInfo,nullptr,&rendererData->debug);
        return instance;
    }
}