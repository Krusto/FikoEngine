//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"
namespace FikoEngine{
    VkDescriptorSetLayout CreateDescriptorSetLayout(RendererDataAPI* rendererData);
    std::vector<VkDescriptorSetLayout> CreateDescriptorSetLayouts(RendererDataAPI* rendererData,u32 count);
    VkDescriptorSet CreateDescriptorSet(RendererDataAPI* rendererData);
    void UpdateDescriptorSet(RendererDataAPI* rendererData,std::vector<VkDescriptorSet>& descriptorSets,u32 index);
    std::vector<VkDescriptorSet> CreateDescriptorSets(RendererDataAPI* rendererData,u32 count);
    VkDescriptorPool CreateDescriptorPool(RendererDataAPI* rendererData);
}