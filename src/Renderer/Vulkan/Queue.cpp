//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Queue.h"
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

    void QueueSubmit(RendererDataAPI* rendererData, uint32_t index) {
        VkSubmitInfo submitInfo{.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO};

        VkSemaphore waitSemaphores[] = {rendererData->imageAvailableSemaphores[index]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &rendererData->commandBuffers[index];

        VkSemaphore signalSemaphores[] = {rendererData->renderFinishedSemaphores[index]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        VK_CHECK(vkQueueSubmit(rendererData->graphicsQueue, 1, &submitInfo, rendererData->inFlightFences[index]));
    }
    VkResult QueuePresent(RendererDataAPI*  rendererData,u32 imageIndex,u32 commandBufferIndex){
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        VkSemaphore signalSemaphores[] = {rendererData->renderFinishedSemaphores[commandBufferIndex]};
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {rendererData->swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        return vkQueuePresentKHR(rendererData->presentQueue, &presentInfo);
    }


}