//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//

#include "Image.h"
namespace FikoEngine {
    std::vector<VkImage> GetSwapchainImages(VkDevice device,VkSwapchainKHR swapchain){
        u32 count{};
        VK_CHECK(vkGetSwapchainImagesKHR(device,swapchain,&count,nullptr));
        std::vector<VkImage> output(count);
        VK_CHECK(vkGetSwapchainImagesKHR(device,swapchain,&count,output.data()));

        return output;
    }
}