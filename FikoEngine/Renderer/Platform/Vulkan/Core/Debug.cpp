//
// Created by krusto on 9/16/19.
//

#include <sstream>
#include <iostream>
#include "Debug.h"
#include "../VulkanCreateInfos.h"
#include "../../../../Logger/Logger.h"

VKAPI_ATTR VkBool32 VKAPI_CALL
dbgFunc(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
        size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
        void *pUserData) {
    std::ostringstream message;

    if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
        message << "ERROR: ";
    } else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
        message << "WARNING: ";
    } else if (msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
        message << "PERFORMANCE WARNING: ";
    } else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
        message << "INFO: ";
    } else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
        message << "DEBUG: ";
    }
    message << "[" << pLayerPrefix << "] Code " << msgCode << " : " << pMsg;

#ifdef _WIN32
    MessageBox(NULL, message.str().c_str(), "Alert", MB_OK);
#else
    std::cout << message.str() << std::endl;
#endif

    /*
     * false indicates that layer should not bail-out of an
     * API call that had validation failures. This may mean that the
     * app dies inside the driver due to invalid parameter(s).
     * That's what would happen without validation layers, so we'll
     * keep that behavior here.
     */
    return false;
}

VkResult FikoEngine::VulkanRenderer::Debug::enableDebug(VkInstance instance,VkDebugReportCallbackEXT* dbgCallback) {
    auto dbgCreateDebugReportCallback =
            (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if (!dbgCreateDebugReportCallback) {
        FIKO_CORE_ERROR( "GetInstanceProcAddr: Unable to find "
                         "vkCreateDebugReportCallbackEXT function.");
    }

    VulkanCreateInfos createInfo;
    createInfo.setDebugReportCallbackCreateInfo(VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT,
                                                dbgFunc);

    return dbgCreateDebugReportCallback(instance, createInfo.getDebugReportCallbackCreateInfo(), NULL,
                                        dbgCallback);
}

