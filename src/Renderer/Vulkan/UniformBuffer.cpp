//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#include "UniformBuffer.h"

namespace FikoEngine{

    Buffer CreateUniformBuffer(RendererDataAPI *rendererData,UniformLayout uniformLayout) {
        u32 bufferSize = uniformLayout.stride;
        Buffer uniformBuffer = Buffer::Create(rendererData->physicalDevice,
                                              rendererData->device,
                                              rendererData->allocator,
                                              bufferSize,
                                              VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        uniformBuffer.size = uniformLayout.stride;
        uniformBuffer.type = BufferType::Uniform;
        uniformBuffer.length = 1;

        return uniformBuffer;
    }
    std::vector<Buffer> CreateUniformBuffers(RendererDataAPI* rendererData,UniformLayout uniformLayout,u32 count){
        std::vector<Buffer> output(count);
        for(u32 i = 0;i < count; ++i)
            output[i] = CreateUniformBuffer(rendererData,uniformLayout);
        return output;
    }

}