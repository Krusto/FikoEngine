//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#include "Renderer/Shader.h"
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

        const VkPipeline& getPipeline() const { return m_Pipeline; }
        VkPipeline& getPipeline() { return m_Pipeline; }

        const VkPipelineLayout& getPipelineLayout() const { return m_PipelineLayout; }
        VkPipelineLayout& getPipelineLayout() { return m_PipelineLayout; }

        virtual void AddResource(std::string_view name, ShaderResourceDeclaration resource) override{};

    private:
        std::unordered_map<std::string, ShaderBuffer> m_Buffers;

        std::string m_Name;
        std::string m_Path;

        VkPipeline m_Pipeline;
        VkPipelineLayout m_PipelineLayout;
    };

}