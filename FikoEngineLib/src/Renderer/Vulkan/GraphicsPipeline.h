//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "RendererData.h"
namespace FikoEngine{
    VkPipeline CreateGraphicsPipeline(VkDevice device,
                                      SwapChainSpec& spec,
                                      VkPipelineLayout& layout,
                                      VkRenderPass renderPass,
                                      VkVertexInputBindingDescription bindingDescription,
                                      std::vector<VkVertexInputAttributeDescription> attributeDescriptions,
                                      VkDescriptorSetLayout& descriptorSetLayout,
                                      std::string_view workingDir,
                                      std::string_view shaderPath);
    void BindGraphicsPipeline(RendererDataAPI*  rendererData,uint32_t imageIndex = {});
    void GraphicsPipelineDraw(RendererDataAPI*  rendererData,uint32_t imageIndex = {});
}