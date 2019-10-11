//
// Created by krusto on 9/29/19.
//

#ifndef FIKOENGINE_SHADER_H
#define FIKOENGINE_SHADER_H

#include <vulkan/vulkan.h>
#include <vector>

namespace FikoEngine::VulkanRenderer {
    class Shader {
    public:
        static VkShaderModule CreateModule(VkDevice logicalDevice,std::vector<uint8_t>data);
    };
}

#endif //FIKOENGINE_SHADER_H
