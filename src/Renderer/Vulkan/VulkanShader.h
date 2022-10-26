//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#include "Renderer/Shader.h"
#include "Swapchain.h"
#include <vulkan/vulkan.h>
#pragma once
namespace FikoEngine{
    void CompileShaderFile(std::string_view workingDir,std::string_view ShaderPath,ShaderType type);
    VkShaderModule CreateShaderModule(VkDevice device, std::string_view workingDir,std::string_view ShaderPath, ShaderType type);

    class VulkanShader : public Shader {
    public:
        VulkanShader(const std::string &path);

        virtual std::unordered_map<std::string, ShaderBuffer> &GetShaderBuffers() override;

        virtual const std::unordered_map<std::string, ShaderResourceDeclaration> &GetResources() const override;

        virtual const std::string &GetName() const override;

        virtual const std::string &GetPath() const override;

        virtual void Reload(bool forceCompile = true) override;

        virtual void Bind() override;

        virtual void SetUniformBuffer(const std::string &name, const void *data, uint32_t size) override;

        virtual void SetStorageBuffer(const std::string &name, const void *data, uint32_t size) override;

        virtual void ResizeStorageBuffer(uint32_t bindingPoint, uint32_t newSize) override;

        virtual void SetUniform(const std::string &fullname, float value) override;

        virtual void SetUniform(const std::string &fullname, int value) override;

        virtual void SetUniform(const std::string &fullname, const glm::ivec2 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::ivec3 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::ivec4 &value) override;

        virtual void SetUniform(const std::string &fullname, uint32_t value) override;

        virtual void SetUniform(const std::string &fullname, const glm::vec2 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::vec3 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::vec4 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::mat3 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::mat4 &value) override;


        const Swapchain& getSwapchain() const { return m_Swapchain;}
        Swapchain& getSwapchain() { return m_Swapchain;}
        void setSwapchain(Swapchain swapchain) { m_Swapchain = swapchain; }

        const VkPipeline& getPipeline() const { return m_Pipeline; }
        VkPipeline& getPipeline() { return m_Pipeline; }

        const VkPipelineLayout& getPipelineLayout() const { return m_PipelineLayout; }
        VkPipelineLayout& getPipelineLayout() { return m_PipelineLayout; }

        const VkCommandPool& getCommandPool() const { return m_CommandPool; }
        VkCommandPool& getCommandPool() { return m_CommandPool; }

        const std::vector<VkCommandBuffer>& getCommandBuffers() const { return m_CommandBuffers; }
        std::vector<VkCommandBuffer>& getCommandBuffers() { return m_CommandBuffers; }

    private:
        std::string m_Name;
        std::string m_Path;

        Swapchain m_Swapchain;
        VkCommandPool m_CommandPool;
        std::vector<VkCommandBuffer> m_CommandBuffers;
        VkPipeline m_Pipeline;
        VkPipelineLayout m_PipelineLayout;
    };

}