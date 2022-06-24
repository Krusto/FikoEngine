//
// Created by Stoyanov, Krusto (K.S.) on 6/24/2022.
//
#include"VertexBuffer.h"

namespace FikoEngine{

Buffer CreateVertexBuffer(RendererDataAPI *rendererData, Vertex* data,VertexLayout vertexLayout, u32 vertexCount) {
    u32 bufferSize = vertexLayout.stride * vertexCount;
    Buffer stagingBuffer = Buffer::Create(rendererData->physicalDevice,
                                          rendererData->device,
                                          rendererData->allocator,
                                          bufferSize,
                                          VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    stagingBuffer.length = vertexCount;
    stagingBuffer.type = BufferType::Staging;
    void* _data{};
    vkMapMemory(rendererData->device, stagingBuffer.memory, 0, bufferSize, 0, &_data);
    memcpy(_data, data, (size_t) bufferSize);
    vkUnmapMemory(rendererData->device, stagingBuffer.memory);

    Buffer vertexBuffer = Buffer::Create(rendererData->physicalDevice,
                                         rendererData->device,
                                         rendererData->allocator,
                                         bufferSize,
                                         VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vertexBuffer.length = vertexCount;
    vertexBuffer.type = BufferType::Vertex;
    Buffer::Copy(rendererData->device,rendererData->commandPool,rendererData->graphicsQueue,stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(rendererData->device, stagingBuffer.buffer, rendererData->allocator);
    vkFreeMemory(rendererData->device, stagingBuffer.memory, rendererData->allocator);

    return vertexBuffer;
}
}