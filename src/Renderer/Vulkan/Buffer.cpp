//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//

#include "Buffer.h"
#include "Command.h"
namespace FikoEngine{

    Buffer Buffer::Create(VkPhysicalDevice physicalDevice,VkDevice device, VkAllocationCallbacks* allocationCallbacks,uint32_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
        Buffer buffer{VK_NULL_HANDLE,BufferType::None,VK_NULL_HANDLE,size,0};
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

        VkMemoryAllocateInfo allocInfo{.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = FindMemoryType(physicalDevice,memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &buffer.memory));

        vkBindBufferMemory(device, buffer.buffer, buffer.memory, 0);

        return buffer;
    }

    void Buffer::Copy(VkDevice device,VkCommandPool commandPool,VkQueue queue,Buffer src, Buffer dst, uint32_t size) {
        std::vector<VkCommandBuffer> commandBuffer(1);
        commandBuffer[0] = CreateCommandBuffer(device,commandPool);;

        BeginCommandBuffer(commandBuffer);

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer[0], src.buffer, dst.buffer, 1, &copyRegion);

        EndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer[0];

        vkQueueSubmit(queue, 1, &submitInfo,VK_NULL_HANDLE);
        vkQueueWaitIdle(queue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer[0]);
    }

    uint32_t Buffer::FindMemoryType(VkPhysicalDevice physicalDevice,uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void
    Buffer::CopyBuffer(VkDevice device, VkCommandPool commandPool, VkQueue queue, Buffer src, Buffer dst, u32 size) {
        VkCommandBuffer commandBuffer{};

        //Create command buffer
        VkCommandBufferAllocateInfo createInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
        createInfo.commandPool = commandPool;
        createInfo.commandBufferCount = 1;
        createInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        VK_CHECK(vkAllocateCommandBuffers(device,&createInfo,&commandBuffer));

        //Begin recording command buffer
        VkCommandBufferBeginInfo beginInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
        VK_CHECK(vkBeginCommandBuffer(commandBuffer,&beginInfo));

        //record copy command
        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, src, dst, 1, &copyRegion);

        // End command buffer
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(queue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }

    void Buffer::Destroy(VkDevice device,VkAllocationCallbacks* callbacks) {
        vkDestroyBuffer(device,buffer, callbacks);
        vkFreeMemory(device, memory, callbacks);
    }
}
