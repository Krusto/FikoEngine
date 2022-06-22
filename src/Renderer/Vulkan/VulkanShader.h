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
    void CompileShaderFile(RendererDataAPI*  rendererData,const char* ShaderPath,ShaderType type);
    VkShaderModule CreateShaderModule(RendererDataAPI*  rendererData,const char* ShaderPath, ShaderType type);
}