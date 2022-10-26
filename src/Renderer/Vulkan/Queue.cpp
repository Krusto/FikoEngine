//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Queue.h"
#include "VulkanContext.h"
#include <vector>
namespace FikoEngine {
    u32 SelectQueueFamily(VkPhysicalDevice physicalDevice) {
        u32 count{};
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
        std::vector<VkQueueFamilyProperties> properties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, properties.data());
        u32 index{};
        for (const auto &property: properties) {
            if ((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT) & property.queueFlags)
                return index;
            index++;
        }
        return index;
    }

    void QueueSubmit(VkQueue queue,std::vector<VkSemaphore>& imageAvailableSemaphores,std::vector<VkSemaphore>& imageFinishedSemaphores,std::vector<VkFence>& fences, uint32_t index) {
        VkSubmitInfo submitInfo{.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO};

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[index]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &VulkanContext::s_RndererData.commandBuffers[index];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[index]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        VK_CHECK(vkQueueSubmit(queue, 1, &submitInfo, fences[index]));
    }
    VkResult QueuePresent(VkQueue queue,Swapchain& swapchain,std::vector<VkSemaphore>& imageFinishedSemaphores,std::vector<VkFence>& fences, uint32_t index,u32 imageIndex,u32 commandBufferIndex){
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[commandBufferIndex]};
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapchain.swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        return vkQueuePresentKHR(queue, &presentInfo);
    }


}