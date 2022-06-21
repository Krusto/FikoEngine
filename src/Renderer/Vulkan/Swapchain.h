//
// Created by Stoyanov, Krusto (K.S.) on 6/10/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "SwapchainSpec.h"
#include "RendererData.h"
#include "../../Core/Core.h"
namespace FikoEngine {

    bool CheckDeviceExtensionSupport(RendererDataAPI& rendererData, std::string_view extension);

    bool CheckSwapChainSupport(RendererDataAPI& rendererData);

    SwapChainSupportDetails GetSwapchainSupportDetails(RendererDataAPI& rendererData);

    VkSurfaceFormatKHR ChooseSurfaceFormat(RendererDataAPI& rendererData);

    VkPresentModeKHR ChoosePresentMode(RendererDataAPI& rendererData);

    VkExtent2D ChooseSwapExtent(RendererDataAPI& rendererData,VkExtent2D windowExtent);

    VkSwapchainKHR CreateSwapchain(RendererDataAPI& rendererData,VkExtent2D windowExtent);
}