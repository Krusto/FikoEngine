//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#ifdef _WIN32
#include <Windows.h>
#endif
#include "VulkanShader.h"
#include "../../Util/File.h"
#include "Memory.h"
#include <vulkan/vulkan.h>
namespace FikoEngine {
    void CompileShaderFile(std::string_view workingDir,std::string_view ShaderPath,ShaderType type){
        #ifdef _WIN32
            auto workDir = std::string(workingDir) + "/" + std::string(ShaderPath);
            std::string command = "glslc " + workDir + " -o " + workDir + ".spv";
            system(command.data());
        #endif
    }
    VkShaderModule CreateShaderModule(VkDevice device, std::string_view workingDir,std::string_view ShaderPath, ShaderType type) {
        FikoEngine::CompileShaderFile(workingDir,ShaderPath,type);
        auto data = File((std::string(workingDir )+ "/" + std::string(ShaderPath)+".spv").data(),FileFormat::Binary).ReadBinaryData();

        VkShaderModuleCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};
        createInfo.codeSize = data.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(data.data());
        VkShaderModule shaderModule{};

        VK_CHECK(vkCreateShaderModule(device,&createInfo,nullptr,&shaderModule));

        LOG_INFO(std::string(ShaderPath) + " shader module created successfully!");
        return shaderModule;
    }
}