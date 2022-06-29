//
// Created by Stoyanov, Krusto (K.S.) on 6/25/2022.
//
#include"VertexBuffer.h"

namespace FikoEngine{

    Buffer CreateIndexBuffer(RendererDataAPI *rendererData, u32* data,u32 count) {
        u32 bufferSize = sizeof(u32) * count;
        Buffer stagingBuffer = Buffer::Create(rendererData->physicalDevice,
                                              rendererData->device,
                                              rendererData->allocator,
                                              bufferSize,
                                              VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        stagingBuffer.type = BufferType::Staging;
        stagingBuffer.length = count;
        stagingBuffer.size = bufferSize;

        void* _data{};
        vkMapMemory(rendererData->device, stagingBuffer.memory, 0, bufferSize, 0, &_data);
        memcpy(_data, data, (size_t) bufferSize);
        vkUnmapMemory(rendererData->device, stagingBuffer.memory);

        Buffer indexBuffer = Buffer::Create(rendererData->physicalDevice,
                                             rendererData->device,
                                             rendererData->allocator,
                                             bufferSize,
                                             VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        indexBuffer.type = BufferType::Index;
        indexBuffer.size = bufferSize;
        indexBuffer.length = count;

        Buffer::Copy(rendererData->device,rendererData->commandPool,rendererData->graphicsQueue,stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(rendererData->device, stagingBuffer.buffer, rendererData->allocator);
        vkFreeMemory(rendererData->device, stagingBuffer.memory, rendererData->allocator);

        return indexBuffer;
    }
}