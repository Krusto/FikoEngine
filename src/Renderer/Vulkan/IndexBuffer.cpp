//
// Created by Stoyanov, Krusto (K.S.) on 6/25/2022.
//
#include"VertexBuffer.h"

namespace FikoEngine{

    Buffer CreateIndexBuffer(VkPhysicalDevice physicalDevice,
                             VkDevice device,
                             VkAllocationCallbacks* allocator,
                             VkQueue graphicsQueue,
                             VkCommandPool commandPool,
                             u32* data,
                             u32 count) {
        u32 bufferSize = sizeof(u32) * count;
        Buffer stagingBuffer = Buffer::Create(physicalDevice,
                                              device,
                                              allocator,
                                              bufferSize,
                                              VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        stagingBuffer.type = BufferType::Staging;
        stagingBuffer.length = count;
        stagingBuffer.size = bufferSize;

        void* _data{};
        vkMapMemory(device, stagingBuffer.memory, 0, bufferSize, 0, &_data);
        memcpy(_data, data, (size_t) bufferSize);
        vkUnmapMemory(device, stagingBuffer.memory);

        Buffer indexBuffer = Buffer::Create(physicalDevice,
                                             device,
                                             allocator,
                                             bufferSize,
                                             VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        indexBuffer.type = BufferType::Index;
        indexBuffer.size = bufferSize;
        indexBuffer.length = count;

        Buffer::Copy(device,commandPool,graphicsQueue,stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(device, stagingBuffer.buffer, allocator);
        vkFreeMemory(device, stagingBuffer.memory, allocator);

        return indexBuffer;
    }
}