//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <vulkan/vulkan.h>

namespace FikoEngine{

    enum class ShaderUniformType {
        None = 0, Bool, Int, UInt, Float, Vec2, Vec3, Vec4, Mat3, Mat4,
        IVec2, IVec3, IVec4
    };
    struct ShaderDataType {
    public:
        static size_t Size(ShaderUniformType Type) {
            switch (Type) {
                case ShaderUniformType::Vec2:
                    return 2 * sizeof(float);
                    break;
                case ShaderUniformType::Vec3:
                    return 3 * sizeof(float);
                    break;
                case ShaderUniformType::Vec4:
                    return 4 * sizeof(float);
                    break;
                case ShaderUniformType::Float:
                    return sizeof(float);
                    break;
            }
            return 0;
        }
        static VkFormat Format(ShaderUniformType Type) {
            switch (Type) {
                case ShaderUniformType::Vec2:
                    return VK_FORMAT_R32G32_SFLOAT;
                    break;
                case ShaderUniformType::Vec3:
                    return VK_FORMAT_R32G32B32_SFLOAT;
                    break;
                case ShaderUniformType::Vec4:
                    return VK_FORMAT_R32G32B32A32_SFLOAT;
                    break;
                case ShaderUniformType::Float:
                    return VK_FORMAT_R32_SFLOAT;
                    break;
            }
            return VK_FORMAT_UNDEFINED;
        }
    };
}