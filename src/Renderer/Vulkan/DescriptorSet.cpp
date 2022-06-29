//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#include "DescriptorSet.h"
#include "../Uniform.h"

namespace FikoEngine{
    VkDescriptorSetLayout CreateDescriptorSetLayout(RendererDataAPI* rendererData){
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

        VkDescriptorSetLayoutCreateInfo layoutInfo{.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        VkDescriptorSetLayout layout{};
        VK_CHECK(vkCreateDescriptorSetLayout(rendererData->device,&layoutInfo,rendererData->allocator,&layout));
        return layout;
    }
    VkDescriptorPool CreateDescriptorPool(RendererDataAPI* rendererData){
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<u32>(rendererData->maxFramesInFlight);

        VkDescriptorPoolCreateInfo poolInfo{.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = static_cast<u32>(rendererData->maxFramesInFlight);

        VkDescriptorPool descriptorPool{};

        VK_CHECK(vkCreateDescriptorPool(rendererData->device,&poolInfo,rendererData->allocator,&descriptorPool));
        return descriptorPool;
    }

    VkDescriptorSet CreateDescriptorSet(RendererDataAPI *rendererData) {
        std::vector<VkDescriptorSetLayout> layouts(rendererData->maxFramesInFlight,rendererData->descriptorSetLayout);
        VkDescriptorSet descriptorSet{};
        VkDescriptorSetAllocateInfo allocInfo{.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
        allocInfo.descriptorPool = rendererData->descriptorPool;
        allocInfo.descriptorSetCount = static_cast<u32>(rendererData->maxFramesInFlight);
        allocInfo.pSetLayouts = layouts.data();

        VK_CHECK(vkAllocateDescriptorSets(rendererData->device, &allocInfo, &descriptorSet));
        return descriptorSet;
    }

    void UpdateDescriptorSet(RendererDataAPI *rendererData,std::vector<VkDescriptorSet>& descriptorSets, u32 index) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = rendererData->uniformBuffers[index];
        bufferInfo.offset = 0;
        bufferInfo.range = MVPUniform::GetLayout().stride;

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = descriptorSets[index];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(rendererData->device, 1, &descriptorWrite, 0, nullptr);
    }

    std::vector<VkDescriptorSet> CreateDescriptorSets(RendererDataAPI *rendererData, u32 count) {

        std::vector<VkDescriptorSetLayout> layouts(rendererData->maxFramesInFlight,rendererData->descriptorSetLayout);
        std::vector<VkDescriptorSet> sets;
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = rendererData->descriptorPool;
        allocInfo.descriptorSetCount = static_cast<u32>(rendererData->maxFramesInFlight);
        allocInfo.pSetLayouts = layouts.data();

        sets.resize(rendererData->maxFramesInFlight);
        VK_CHECK(vkAllocateDescriptorSets(rendererData->device, &allocInfo, sets.data()));

        for (size_t i = 0; i < rendererData->maxFramesInFlight; i++) {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = rendererData->uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = rendererData->uniformBuffers[0].size;

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = sets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;

            vkUpdateDescriptorSets(rendererData->device, 1, &descriptorWrite, 0, nullptr);
        }
        return sets;
    }

    std::vector<VkDescriptorSetLayout> CreateDescriptorSetLayouts(RendererDataAPI* rendererData,u32 count) {
        std::vector<VkDescriptorSetLayout> layouts(count);
        VkDescriptorSetLayout layout = CreateDescriptorSetLayout(rendererData);
        for (u32 i = 0; i < count; ++i)
            layouts[i] = layout;
        return layouts;
    }

};