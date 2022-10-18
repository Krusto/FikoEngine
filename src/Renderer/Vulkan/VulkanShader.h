//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#include "RendererData.h"
#include <vulkan/vulkan.h>
#pragma once
namespace FikoEngine{
    enum class ShaderType{
        None,
        Vertex,
        Fragment,
        Compute
    };
    void CompileShaderFile(std::string_view workingDir,std::string_view ShaderPath,ShaderType type);
    VkShaderModule CreateShaderModule(VkDevice device, std::string_view workingDir,std::string_view ShaderPath, ShaderType type);
}