//
// Created by krusto on 1.09.19 г..
//

#ifndef FIKOENGINE_VULKANCREATEINFOS_H
#define FIKOENGINE_VULKANCREATEINFOS_H
#include <vulkan/vulkan.h>
#include <vector>
namespace FikoEngine::VulkanRenderer {
    class VulkanCreateInfos {
    public:
        VulkanCreateInfos();

        void setInstanceAttr(std::vector<const char*>* Layers,std::vector<const char*>* Extensions);
        void setDeviceAttr(std::vector<const char*> Extensions,std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos);
        void setQueueFamilyAttr(uint32_t QueueFamilyIndex);

        VkInstanceCreateInfo* getVkInstance();
        VkApplicationInfo* getApplicationInfo();
        VkDeviceCreateInfo* getDeviceCreateInfo();
        VkDeviceQueueCreateInfo* getDeviceQueueCreateInfo(int index);
        VkDebugReportCallbackCreateInfoEXT* getDebugReportCallbackCreateInfo();

        void setVkInstanceCreateInfo( const VkApplicationInfo*    pApplicationInfo,
                                      uint32_t                    enabledLayerCount,
                                      const char* const*          ppEnabledLayerNames,
                                      uint32_t                    enabledExtensionCount,
                                      const char* const*          ppEnabledExtensionNames,
                                      VkStructureType             sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                      const void*                 pNext = nullptr,
                                      VkInstanceCreateFlags       flags = 0);

        void setVkApplicationInfo(  const char*        pApplicationName,
                                    uint32_t           applicationVersion,
                                    const char*        pEngineName,
                                    uint32_t           engineVersion,
                                    uint32_t           apiVersion,
                                    VkStructureType    sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                    const void*        pNext = nullptr);

        void setVkQueueCreateInfo(  VkDeviceQueueCreateFlags    flags,
                                    uint32_t                    queueFamilyIndex,
                                    uint32_t                    queueCount,
                                    const float*                pQueuePriorities,
                                    VkStructureType             sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                                    const void*                 pNext = nullptr);

        void setVkDeviceCreateInfo( uint32_t                           queueCreateInfoCount,
                                    const VkDeviceQueueCreateInfo*     pQueueCreateInfos,
                                    uint32_t                           enabledExtensionCount,
                                    const char* const*                 ppEnabledExtensionNames,
                                    const VkPhysicalDeviceFeatures*    pEnabledFeatures,
                                    VkStructureType                    sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                                    const void*                        pNext = nullptr,
                                    VkDeviceCreateFlags                flags = 0);

        void setDebugReportCallbackCreateInfo(  VkDebugReportFlagsEXT           flags,
                                                PFN_vkDebugReportCallbackEXT    pfnCallback,
                                                void*                           pUserData = nullptr,
                                                VkStructureType                 sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
                                                const void*                     pNext = nullptr);

    private:
        VkInstanceCreateInfo mInstanceCreateInfo;
        VkApplicationInfo mApplicationInfo;
        VkDeviceCreateInfo mDeviceCreateInfo;
        VkDebugReportCallbackCreateInfoEXT mDebugCallbackCreateInfoEXT;

        std::vector<VkDeviceQueueCreateInfo> mDeviceQueueCreateInfo;

    private:
        struct mInstanceAttr{
            std::vector<const char*> Layers;
            std::vector<const char*> Extensions;
        }mInstanceAttr;
        struct mDeviceAttr{
            std::vector<const char*> Extensions;
            std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
        }mDeviceAttr;
        struct mQueueFamilyAttr{
            uint32_t queueFamilyIndex;
        }mQueueFamilyAttr;
    };
}

#endif //FIKOENGINE_VULKANCREATEINFOS_H
