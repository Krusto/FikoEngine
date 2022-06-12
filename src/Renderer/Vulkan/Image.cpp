//
// Created by KSTOYAN2 on 6/11/2022.
//

#include "Image.h"
namespace FikoEngine {
    std::vector<VkImage> GetSwapchainImages(RendererDataAPI& rendererData){
        u32 count{};
        VK_CHECK(vkGetSwapchainImagesKHR(rendererData.device,rendererData.swapchain,&count,nullptr));
        std::vector<VkImage> output(count);
        VK_CHECK(vkGetSwapchainImagesKHR(rendererData.device,rendererData.swapchain,&count,output.data()));

        return output;
    }
}