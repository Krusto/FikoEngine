#pragma once

#include <glad/glad.h>
#include <Renderer/Shader.h>
#include <Renderer/ShaderUniform.h>

namespace FikoEngine {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader();
        OpenGLShader(const std::string &filepath, bool forceRecompile);

        static Ref<OpenGLShader> CreateFromString(const std::string &source);

        virtual void Reload(bool forceCompile = true) override;

        virtual void Bind() override;

        static const ShaderUniformBuffer &FindUniformBuffer(const std::string &name) { return s_UniformBuffers[0];}

        static void SetUniformBuffer(const ShaderUniformBuffer &buffer, const void *data, u32 size, u32 offset = 0) {}

        static void SetStorageBuffer(const ShaderStorageBuffer &buffer, const void *data, u32 size, u32 offset = 0) {}

        virtual void SetUniformBuffer(const std::string &name, const void *data, u32 size) override {}

        virtual void SetStorageBuffer(const std::string &name, const void *data, u32 size) override {}

        virtual void ResizeStorageBuffer(u32 bindingPoint, u32 newSize) override {}

        virtual void SetUniform(const std::string &fullname, float value) override;

        virtual void SetUniform(const std::string &fullname, int value) override;

        virtual void SetUniform(const std::string &fullname, const glm::ivec2 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::ivec3 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::ivec4 &value) override;

        virtual void SetUniform(const std::string &fullname, u32 value) override;

        virtual void SetUniform(const std::string &fullname, const glm::vec2 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::vec3 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::vec4 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::mat3 &value) override;

        virtual void SetUniform(const std::string &fullname, const glm::mat4 &value) override;

        virtual const std::string &GetName() const override { return m_Name; }
        virtual const std::string &GetPath() const override { return m_AssetPath; }

        virtual std::unordered_map<std::string, ShaderBuffer> &GetShaderBuffers() override { return m_Buffers; }

        virtual const std::unordered_map<std::string, ShaderResourceDeclaration> &
        GetResources() const override { return m_Resources; }

        const ShaderResourceDeclaration *GetShaderResource(const std::string &name);

        static void ClearUniformBuffers();

        void Load(const std::string &source, bool forceCompile);

        virtual void AddResource(std::string_view name, ShaderResourceDeclaration resource) override;
    private:
        void Compile(const std::string &vertexData, const std::string &fragmentData);

        void Reflect(std::vector<u32> &data) {}

        void CheckShader(GLuint id, GLuint type, GLint *ret, const char *onfail);

        void CompileOrGetVulkanBinary(std::unordered_map<u32, std::vector<u32>> &outputBinary,
                                      bool forceCompile = false) {}

        void CompileOrGetOpenGLBinary(const std::unordered_map<u32, std::vector<u32>> &,
                                      bool forceCompile = false) {}

        std::string ReadShaderFromFile(const std::string &filepath, ShaderType shaderType) const;

        std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);

        int32_t GetUniformLocation(const std::string &name) const;

        static GLenum ShaderTypeFromString(const std::string &type) {
            if (type == "vertex")
                return GL_VERTEX_SHADER;
            if (type == "fragment" || type == "pixel")
                return GL_FRAGMENT_SHADER;
            if (type == "compute")
                return GL_COMPUTE_SHADER;

            return GL_NONE;
        }

        void UploadUniformInt(u32 location, int32_t value);

        void UploadUniformIntArray(u32 location, int32_t *values, int32_t count);

        void UploadUniformFloat(u32 location, float value);

        void UploadUniformFloat2(u32 location, const glm::vec2 &value);

        void UploadUniformFloat3(u32 location, const glm::vec3 &value);

        void UploadUniformFloat4(u32 location, const glm::vec4 &value);

        void UploadUniformMat3(u32 location, const glm::mat3 &values);

        void UploadUniformMat4(u32 location, const glm::mat4 &values);

        void UploadUniformMat4Array(u32 location, const glm::mat4 &values, u32 count);

        void UploadUniformInt(const std::string &name, int32_t value);

        void UploadUniformUInt(const std::string &name, u32 value);

        void UploadUniformIntArray(const std::string &name, int32_t *values, u32 count);

        void UploadUniformFloat(const std::string &name, float value);

        void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);

        void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);

        void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

        void UploadUniformMat4(const std::string &name, const glm::mat4 &value);

    private:
        u32 m_RendererID = 0;
        bool m_Loaded = false;
        bool m_IsCompute = false;

        u32 m_ConstantBufferOffset = 0;

        std::string m_Name, m_AssetPath;
        std::unordered_map<GLenum, std::string> m_ShaderSource;

        inline static std::unordered_map<u32, ShaderUniformBuffer> s_UniformBuffers;
        inline static std::unordered_map<u32, ShaderStorageBuffer> s_StorageBuffers;

        std::unordered_map<std::string, ShaderBuffer> m_Buffers;
        std::unordered_map<std::string, ShaderResourceDeclaration> m_Resources;
        std::unordered_map<std::string, GLint> m_UniformLocations;

        bool m_Compiled = false;
    };

}