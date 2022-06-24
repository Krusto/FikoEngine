//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <vulkan/vulkan.h>

namespace FikoEngine{
    struct ShaderDataType {
    public:
        enum class ShaderType {vec1,vec2, vec3, vec4, };
        static size_t Size(ShaderType Type) {
            switch (Type) {
                case ShaderType::vec2:
                    return 2 * sizeof(float);
                    break;
                case ShaderType::vec3:
                    return 3 * sizeof(float);
                    break;
                case ShaderType::vec4:
                    return 4 * sizeof(float);
                    break;
                case ShaderType::vec1:
                    return sizeof(float);
                    break;
            }
            return 0;
        }
        static VkFormat Format(ShaderType Type) {
            switch (Type) {
                case ShaderType::vec2:
                    return VK_FORMAT_R32G32_SFLOAT;
                    break;
                case ShaderType::vec3:
                    return VK_FORMAT_R32G32B32_SFLOAT;
                    break;
                case ShaderType::vec4:
                    return VK_FORMAT_R32G32B32A32_SFLOAT;
                    break;
                case ShaderType::vec1:
                    return VK_FORMAT_R32_SFLOAT;
                    break;
            }
            return VK_FORMAT_UNDEFINED;
        }
    };
}