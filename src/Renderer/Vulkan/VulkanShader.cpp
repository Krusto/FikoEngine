//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#ifdef _WIN32
#include <Windows.h>
#endif
#include "VulkanShader.h"
#include "../../Util/File.h"
#include "Memory.h"
#include "VulkanContext.h"
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
    VulkanShader::VulkanShader(const std::string &path) {

        m_Swapchain.swapchain = CreateSwapchain(VulkanContext::s_RendererData.physicalDevice,
                                                VulkanContext::s_RendererData.device,
                                                m_Swapchain.SwapchainSpec,
                                                m_Swapchain.Surface,
                                                VulkanContext::s_RendererData.queueFamilyIndex,
                                                VulkanContext::s_RendererData.rendererSpec.SurfaceSize

        );

        m_Swapchain.FrameSize = VulkanContext::s_RendererData.rendererSpec.SurfaceSize;
        m_Path = path;
        SwapchainRecreate(m_Swapchain,
                          VulkanContext::s_RendererData.physicalDevice,
                          VulkanContext::s_RendererData.device,
                          m_Swapchain.FrameSize,
                          VulkanContext::s_RendererData.workingDir,
                          m_Path);

        s_RendererData.commandPool = CreateCommandPool(s_RendererData.device,s_RendererData.queueFamilyIndex);

//        s_RendererData.vertexBuffer = CreateVertexBuffer(&s_RendererData);

        s_RendererData.commandBuffers = CreateCommandBuffers(s_RendererData.device,s_RendererData.commandPool,s_RendererData.imageViews.size());

    }
    std::unordered_map<std::string, ShaderBuffer> &VulkanShader::GetShaderBuffers() {
        return {};
    }

    const std::unordered_map<std::string, ShaderResourceDeclaration> &VulkanShader::GetResources() const {
        return {};
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