//
// Created by krusto on 1.09.19 г..
//

#include <vector>
#include "VulkanCreateInfos.h"

namespace FikoEngine::VulkanRenderer{

    VulkanCreateInfos::VulkanCreateInfos() {
        setVkApplicationInfo("appName",VK_MAKE_VERSION(1,0,0),"FikoEngine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0));
        setVkInstanceCreateInfo(getApplicationInfo(),mInstanceAttr.Layers.size(),mInstanceAttr.Layers.data(),mInstanceAttr.Extensions.size(),mInstanceAttr.Extensions.data());
    }

    void VulkanCreateInfos::setInstanceAttr(std::vector<const char *>* Layers, std::vector<const char *>* Extensions) {
        mInstanceAttr = {*Layers,*Extensions};
        mInstanceCreateInfo.enabledLayerCount = mInstanceAttr.Layers.size();
        mInstanceCreateInfo.ppEnabledLayerNames = mInstanceAttr.Layers.data();
        mInstanceCreateInfo.enabledExtensionCount = mInstanceAttr.Extensions.size();
        mInstanceCreateInfo.ppEnabledExtensionNames = mInstanceAttr.Extensions.data();
    }
    void VulkanCreateInfos::setDeviceAttr(std::vector<const char *> Extensions,std::vector<VkDeviceQueueCreateInfo> QueueCreateInfo) {
        mDeviceAttr = {Extensions,QueueCreateInfo};
    }
    void VulkanCreateInfos::setQueueFamilyAttr(uint32_t QueueFamilyIndex) {
        mQueueFamilyAttr = {QueueFamilyIndex};
    }
    VkInstanceCreateInfo* VulkanCreateInfos::getVkInstance() {
        return &mInstanceCreateInfo;
    }

    VkApplicationInfo* VulkanCreateInfos::getApplicationInfo() {
        return &mApplicationInfo;
    }

    VkDeviceCreateInfo *VulkanCreateInfos::getDeviceCreateInfo() {
        return &mDeviceCreateInfo;
    }
    VkDeviceQueueCreateInfo* VulkanCreateInfos::getDeviceQueueCreateInfo(int index) {
        return &mDeviceQueueCreateInfo[index];
    }
    VkDebugReportCallbackCreateInfoEXT *VulkanCreateInfos::getDebugReportCallbackCreateInfo() {
        return &mDebugCallbackCreateInfoEXT;
    }
    VkSwapchainCreateInfoKHR *VulkanCreateInfos::getSwapchainCreateInfo() {
        return &mSwapchainCreateInfo;
    }

    void VulkanCreateInfos::setVkInstanceCreateInfo(const VkApplicationInfo *pApplicationInfo, uint32_t enabledLayerCount,
                                               const char *const *ppEnabledLayerNames, uint32_t enabledExtensionCount,
                                               const char *const *ppEnabledExtensionNames, VkStructureType sType,
                                               const void *pNext, VkInstanceCreateFlags flags) {
        mInstanceCreateInfo = {sType,pNext,flags,pApplicationInfo,enabledLayerCount,ppEnabledLayerNames,enabledExtensionCount,ppEnabledExtensionNames};
    }

    void VulkanCreateInfos::setVkApplicationInfo(const char *pApplicationName, uint32_t applicationVersion,
                                                 const char *pEngineName, uint32_t engineVersion, uint32_t apiVersion,
                                                 VkStructureType sType, const void *pNext) {
        mApplicationInfo = {sType,pNext,pApplicationName,applicationVersion,pEngineName,engineVersion,apiVersion};
    }

    void VulkanCreateInfos::setVkDeviceCreateInfo(uint32_t queueCreateInfoCount,
                                                  const VkDeviceQueueCreateInfo *pQueueCreateInfos,
                                                  uint32_t enabledExtensionCount,
                                                  const char *const *ppEnabledExtensionNames,
                                                  const VkPhysicalDeviceFeatures *pEnabledFeatures,
                                                  VkStructureType sType, const void *pNext, VkDeviceCreateFlags flags) {

        mDeviceCreateInfo = {sType,pNext,flags,queueCreateInfoCount,pQueueCreateInfos,0,nullptr,enabledExtensionCount,ppEnabledExtensionNames,pEnabledFeatures};

    }

    void VulkanCreateInfos::setVkQueueCreateInfo(VkDeviceQueueCreateFlags flags, uint32_t queueFamilyIndex,
                                                 uint32_t queueCount, const float *pQueuePriorities,
                                                 VkStructureType sType, const void *pNext) {
        mDeviceQueueCreateInfo.emplace_back((VkDeviceQueueCreateInfo){sType,pNext,flags,queueFamilyIndex,queueCount,pQueuePriorities});

    }

    void VulkanCreateInfos::setDebugReportCallbackCreateInfo(VkDebugReportFlagsEXT flags,
                                                             PFN_vkDebugReportCallbackEXT pfnCallback, void *pUserData,
                                                             VkStructureType sType, const void *pNext) {
        mDebugCallbackCreateInfoEXT = {sType,pNext,flags,pfnCallback,pUserData};
    }

    void VulkanCreateInfos::setSwapchainCreateInfo(VkSwapchainCreateFlagsKHR flags, VkSurfaceKHR surface,
                                                   uint32_t minImageCount, VkFormat imageFormat,
                                                   VkColorSpaceKHR imageColorSpace, VkExtent2D imageExtent,
                                                   uint32_t imageArrayLayers, VkImageUsageFlags imageUsage,
                                                   VkSharingMode imageSharingMode, uint32_t queueFamilyIndexCount,
                                                   const uint32_t *pQueueFamilyIndices,
                                                   VkSurfaceTransformFlagBitsKHR preTransform,
                                                   VkCompositeAlphaFlagBitsKHR compositeAlpha,
                                                   VkPresentModeKHR presentMode, VkBool32 clipped,
                                                   VkSwapchainKHR oldSwapchain, VkStructureType sType,
                                                   const void *pNext) {
        mSwapchainCreateInfo = {sType,pNext,flags,surface,minImageCount,imageFormat,imageColorSpace,imageExtent,imageArrayLayers,imageUsage,imageSharingMode,queueFamilyIndexCount,pQueueFamilyIndices,preTransform,compositeAlpha,presentMode,clipped,oldSwapchain};

    }


}