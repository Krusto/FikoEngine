//
// Created by krusto on 9/29/19.
//

#include <vulkan/vulkan.h>
#include "GraphicsPipeline.h"
#include "../VulkanUtilities.h"
#include "Shader.h"

namespace FikoEngine::VulkanRenderer {
    void GraphicsPipeline::Create(VkDevice logicalDevice,const std::string &VertexShaderPath, const std::string &FragmentShaderPath,
                                  FikoEngine::Window *window) {

        auto vertShader = OpenFile(VertexShaderPath);
        auto fragShader = OpenFile(FragmentShaderPath);

        VkShaderModule vertShaderModule = Shader::CreateModule(logicalDevice,vertShader);
        VkShaderModule fragShaderModule = Shader::CreateModule(logicalDevice,fragShader);

        vkDestroyShaderModule(logicalDevice, vertShaderModule, nullptr);
        vkDestroyShaderModule(logicalDevice, fragShaderModule, nullptr);
    }

    void GraphicsPipeline::Bind(VkPipeline graphicsPipeline) {
//        vkCmdBindPipeline()
    }
}