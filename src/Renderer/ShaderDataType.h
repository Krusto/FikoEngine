//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <vulkan/vulkan.h>

namespace FikoEngine
{
    struct ShaderDataType 
    {
    public:
        enum class ShaderType { vec1, vec2, vec3, vec4, }; // Can be optimized. The enum type could be set to u8, since the values are only 4
        
        static std::size_t Size(ShaderType type) 
        {
            switch (type) 
            {
                case ShaderType::vec2: return 2 * sizeof(float); // NO NEED TO BREAK, SINCE YOU ARE RETURNING
                case ShaderType::vec3: return 3 * sizeof(float);
                case ShaderType::vec4: return 4 * sizeof(float);
                case ShaderType::vec1: return sizeof(float);    
            }
            return 0;
        }
        
        static VkFormat Format(ShaderType Typtypee) 
        {
            switch (type) 
            {
                case ShaderType::vec2: return VK_FORMAT_R32G32_SFLOAT; // NO NEED TO BREAK, SINCE YOU ARE RETURNING
                case ShaderType::vec3: return VK_FORMAT_R32G32B32_SFLOAT;
                case ShaderType::vec4: return VK_FORMAT_R32G32B32A32_SFLOAT;
                case ShaderType::vec1: return VK_FORMAT_R32_SFLOAT;
            }
            return VK_FORMAT_UNDEFINED;
        }
    };
}
