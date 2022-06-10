#include "Swapchain.h"
namespace FikoEngine {
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device, std::string_view extension) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        for (const auto &availableExtension: availableExtensions) {
            if (extension == availableExtension.extensionName)
                return true;
        }
        return false;
    }

    bool CheckSwapChainSupport(VkPhysicalDevice physicalDevice) {
        bool isExtensionPresent = CheckDeviceExtensionSupport(physicalDevice, VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        if (!isExtensionPresent) {
            LOG_ERROR("VK_KHR_swapchain extension not supported!");
        }
        return isExtensionPresent;
    }
}