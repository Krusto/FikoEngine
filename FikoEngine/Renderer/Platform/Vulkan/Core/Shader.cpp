//
// Created by krusto on 9/29/19.
//

#include "Shader.h"

VkShaderModule FikoEngine::VulkanRenderer::Shader::CreateModule(VkDevice logicalDevice,std::vector<uint8_t>data) {
    VkShaderModuleCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pNext = NULL;
    createInfo.codeSize = data.size();
    createInfo.flags = 0;
    createInfo.pCode = reinterpret_cast<const uint32_t*>(data.data());
    VkShaderModule module = 0;
    vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &module);

    return nullptr;
}
