//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//

#include "Buffer.h"
#include "Command.h"
namespace FikoEngine{

    Buffer Buffer::Create(VkPhysicalDevice physicalDevice,VkDevice device, VkAllocationCallbacks* allocationCallbacks,uint32_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
        Buffer buffer{VK_NULL_HANDLE,BufferType::None,VK_NULL_HANDLE,size};
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VK_CHECK(vkCreateBuffer(device, &bufferInfo, allocationCallbacks, &buffer.buffer));

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer.buffer, &memRequirements);

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        u32 memoryType{};
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((memRequirements.memoryTypeBits & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
                memoryType = i;
            }
        }

        VkMemoryAllocateInfo allocInfo{.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = memoryType;

        VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &buffer.memory));

        vkBindBufferMemory(device, buffer.buffer, buffer.memory, 0);

        return buffer;
    }

    void Buffer::Copy(VkDevice device,VkCommandPool commandPool,VkQueue queue,Buffer src, Buffer dst, uint32_t size) {
        VkCommandBuffer commandBuffer = CreateCommandBuffer(device,commandPool);;

        BeginCommandBuffer(commandBuffer);

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, src.buffer, dst.buffer, 1, &copyRegion);

        EndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(queue, 1, &submitInfo,VK_NULL_HANDLE);
        vkQueueWaitIdle(queue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }
}
