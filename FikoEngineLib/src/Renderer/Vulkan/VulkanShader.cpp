//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#ifdef _WIN32
#include <Windows.h>
#endif
#include "VulkanShader.h"
#include "../../Util/File.h"
#include "Memory.h"
#include "VulkanRenderer.h"
#include "Renderer/Vertex.h"
#include "GraphicsPipeline.h"
#include <vulkan/vulkan.h>
#include <filesystem>
namespace FikoEngine {
    void CompileShaderFile(std::string_view workingDir,std::string_view ShaderPath,ShaderType type){

        #ifdef _WIN32
    //       auto file = std::string(workingDir) + "/" + std::string(ShaderPath);
            auto file = std::filesystem::current_path().string() + "/" + std::string(ShaderPath);
            std::string command = "glslc " + file + " -o " + file + ".spv";
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

        return shaderModule;
    }
    VulkanShader::VulkanShader(const std::string &path) {
        m_Path = path;
        m_Pipeline = CreateGraphicsPipeline(
                VulkanRenderer::s_RendererData.device,
                VulkanRenderer::s_RendererData.swapchainSpec,
                m_PipelineLayout,
                VulkanRenderer::s_RendererData.renderPass,
                Vertex::GetBindingDescription(),
                Vertex::GetAttributeDescriptions(),
                VulkanRenderer::s_RendererData.descriptorSetLayout,
                VulkanRenderer::s_RendererData.workingDir,
                m_Path);
    }
    std::unordered_map<std::string, ShaderBuffer> &VulkanShader::GetShaderBuffers() {
        return m_Buffers;
    }
    const std::unordered_map<std::string, ShaderBuffer> &VulkanShader::GetShaderBuffers() const {
        return m_Buffers;
    }

    const std::unordered_map<std::string, ShaderResourceDeclaration> &VulkanShader::GetResources() const {
        return m_Resources;
    }

    const std::string &VulkanShader::GetName() const {
        return m_Name;
    }

    const std::string &VulkanShader::GetPath() const {
        return m_Path;
    }

    void VulkanShader::Reload(bool forceCompile) {

    }

    void VulkanShader::Bind() {
        VulkanRenderer::s_RendererData.currentShader = Ref<Shader>(this);
    }

    void VulkanShader::SetUniformBuffer(const std::string &name, const void *data, uint32_t size) {

    }

    void VulkanShader::SetStorageBuffer(const std::string &name, const void *data, uint32_t size) {

    }

    void VulkanShader::ResizeStorageBuffer(uint32_t bindingPoint, uint32_t newSize) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, float value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, int value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::ivec2 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::ivec3 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::ivec4 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, uint32_t value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::vec2 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::vec3 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::vec4 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::mat3 &value) {

    }

    void VulkanShader::SetUniform(const std::string &fullname, const glm::mat4 &value) {

    }



}