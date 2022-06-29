//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../Core/Math.h"
namespace FikoEngine{
    struct UniformDataType {
    public:
        enum class UniformType {vec1,vec2, vec3, vec4,mat3,mat4 };
        static size_t Size(UniformType Type) {
            switch (Type) {
                case UniformType::vec2:
                    return sizeof(FikoEngine::vec2);
                    break;
                case UniformType::vec3:
                    return sizeof(FikoEngine::vec3);
                    break;
                case UniformType::vec4:
                    return sizeof(FikoEngine::vec4);
                    break;
                case UniformType::vec1:
                    return sizeof(float);
                    break;
                case UniformType::mat3:
                    return sizeof(FikoEngine::mat3);
                    break;
                case UniformType::mat4:
                    return sizeof(FikoEngine::mat4);

                    break;
            }
            return 0;
        }
        static VkFormat Format(UniformType Type) {
            switch (Type) {
                case UniformType::vec2:
                    return VK_FORMAT_R32G32_SFLOAT;
                    break;
                case UniformType::vec3:
                    return VK_FORMAT_R32G32B32_SFLOAT;
                    break;
                case UniformType::vec4:
                    return VK_FORMAT_R32G32B32A32_SFLOAT;
                    break;
                case UniformType::vec1:
                    return VK_FORMAT_R32_SFLOAT;
                    break;
            }
            return VK_FORMAT_UNDEFINED;
        }
    };
}