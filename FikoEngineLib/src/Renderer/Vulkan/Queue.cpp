//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Queue.h"
#include "VulkanRenderer.h"
#include <vector>
namespace FikoEngine {
    uint32_t SelectQueueFamily(VkPhysicalDevice physicalDevice) {
        uint32_t count{};
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
        std::vector<VkQueueFamilyProperties> properties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, properties.data());
        uint32_t index{};
        for (const auto &property: properties) {
            if ((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT) & property.queueFlags)
                return index;
            index++;
        }
        return index;
    }

    void QueueSubmit(VkQueue queue,std::vector<VkSemaphore>& imageAvailableSemaphores,std::vector<VkSemaphore>& renderFinishedSemaphores,std::vector<VkFence>& fences, uint32_t index) {
        VkSubmitInfo submitInfo{.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO};

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[index]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &VulkanRenderer::s_RendererData.commandBuffers[index];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[index]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        VK_CHECK(vkQueueSubmit(queue, 1, &submitInfo, fences[index]));
    }
    VkResult QueuePresent(VkQueue queue,Ref<Swapchain> swapchain,std::vector<VkSemaphore>& renderFinishedSemaphores,std::vector<VkFence>& fences, uint32_t imageIndex, uint32_t currentFrameIndex){
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrameIndex]};
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapchain->GetSwapchain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        return vkQueuePresentKHR(queue, &presentInfo);
    }


}