#pragma once

#include <map>
#include <Core/Buffer.h>
#include <Renderer/Material.h>
#include <Renderer/Texture.h>
namespace FikoEngine {

    class OpenGLMaterial : public Material {
    public:
        OpenGLMaterial(WeakRef<Shader> shader,std::string_view name);

        explicit OpenGLMaterial(std::string_view name);

        ~OpenGLMaterial() override;

        void Set(std::string_view name, float value) override;

        void Set(std::string_view name, int value) override;

        void Set(std::string_view name, uint32_t value) override;

        void Set(std::string_view name, bool value) override;

        void Set(std::string_view name, const glm::ivec2 &value) override;

        void Set(std::string_view name, const glm::ivec3 &value) override;

        void Set(std::string_view name, const glm::ivec4 &value) override;

        void Set(std::string_view name, const glm::vec2 &value) override;

        void Set(std::string_view name, const glm::vec3 &value) override;

        void Set(std::string_view name, const glm::vec4 &value) override;

        void Set(std::string_view name, const glm::mat3 &value) override;

        void Set(std::string_view name, const glm::mat4 &value) override;

        void Set(std::string_view name, WeakRef<Texture> texture) override;

        void Set(std::string_view name, WeakRef<Texture> texture, uint32_t arrayIndex) override;

        float &GetFloat(std::string_view name) override;

        int32_t &GetInt(std::string_view name) override;

        uint32_t &GetUInt(std::string_view name) override;

        bool &GetBool(std::string_view name) override;

        glm::vec2 &GetVector2(std::string_view name) override;

        glm::vec3 &GetVector3(std::string_view name) override;

        glm::vec4 &GetVector4(std::string_view name) override;

        glm::mat3 &GetMatrix3(std::string_view name) override;

        glm::mat4 &GetMatrix4(std::string_view name) override;

        WeakRef<Texture> GetTexture(std::string_view name) override;

        WeakRef<Texture> TryGetTexture(std::string_view name) override;

        const float &GetFloat(std::string_view name) const override;

        const int32_t &GetInt(std::string_view name) const override;

        const uint32_t &GetUInt(std::string_view name) const override;

        const bool &GetBool(std::string_view name) const override;

        const glm::vec2 &GetVector2(std::string_view name) const override;

        const glm::vec3 &GetVector3(std::string_view name) const override;

        const glm::vec4 &GetVector4(std::string_view name) const override;

        const glm::mat3 &GetMatrix3(std::string_view name) const override;

        const glm::mat4 &GetMatrix4(std::string_view name) const override;

        WeakRef<Texture> GetTexture(std::string_view  name) const override;

        WeakRef<Texture> TryGetTexture(std::string_view name) const override;

        template<typename T>
        void Set(std::string_view name, const T &value, ShaderUniformType type, uint32_t size) {
            if(m_Shader.IsValid()) {
                auto shader = m_Shader.Lock();
                auto &shaderBuffer = shader->GetShaderBuffers()["shaderBuffer"];
                shaderBuffer.Size += 1;

                std::string uniformName = std::string(name);
                auto &uniform = shaderBuffer.Uniforms[uniformName];
                uniform.m_Name = uniformName;
                uniform.m_Offset = shader->offset;
                uniform.m_Size = size;
                uniform.m_Type = type;

                auto &buffer = m_UniformStorageBuffer;

                buffer->Write((byte *) &value, size, shader->offset);
                shader->offset += size;
            }
        }

        template<typename T>
        T &Get(std::string_view name) {
            auto decl = FindUniformDeclaration(name);
            assert(decl);
//			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
            auto &buffer = m_UniformStorageBuffer;
            return buffer->Read<T>(decl->GetOffset());
        }

        template<typename T>
        const T &Get(std::string_view name) const {
            auto decl = FindUniformDeclaration(name);
            assert(decl);
//			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
            auto &buffer = m_UniformStorageBuffer;
            return buffer->Read<T>(decl->GetOffset());
        }

        template<typename T>
        WeakRef<T> GetResource(std::string_view name) {
            (void)name;
            return {};
        }

        template<typename T>
        WeakRef<T> TryGetResource(std::string_view name) {
            auto resourceDeclaration = FindResourceDeclaration(name);

            if (resourceDeclaration != nullptr) {
                if (resourceDeclaration->GetRegister() < m_Textures.size()) {
                    if(m_Textures[resourceDeclaration->GetRegister()].IsValid())
                        return m_Textures[resourceDeclaration->GetRegister()];
                }
            }
            return {};
        }
        
        template<typename T>
        WeakRef<T> TryGetResource(std::string_view name) const {
            auto resourceDeclaration = FindResourceDeclaration(name);

            if (resourceDeclaration != nullptr) {
                if (resourceDeclaration->GetRegister() < m_Textures.size()) {
                    if(m_Textures[resourceDeclaration->GetRegister()].IsValid())
                        return m_Textures[resourceDeclaration->GetRegister()];
                }
            }
            return {};
        }

        WeakRef<Shader> GetShader() override { return m_Shader; }
        WeakRef<Shader> GetShader() const override { return m_Shader; }

        void SetShader(WeakRef<Shader> shader) override { m_Shader = shader; };

        std::string_view GetName() const override { return m_Name; }

        Ref<Buffer> GetUniformStorageBuffer() { return m_UniformStorageBuffer; }

        void UpdateForRendering() override;

        Buffer &GetBuffer() override { return *m_UniformStorageBuffer; };

        void Reset() override {
            if(m_Shader.IsValid()) {
                auto shader = m_Shader.Lock();
                shader->Reload(true);
            }
        }

        bool HasDiffuseTexture() override;

        bool HasSpecularTexture() override;

    private:
        void AllocateStorage();

        void OnShaderReloaded();

        const ShaderUniform *FindUniformDeclaration(std::string_view name);
        const ShaderUniform *FindUniformDeclaration(std::string_view name) const;

        const ShaderResourceDeclaration *FindResourceDeclaration(std::string_view name);
        const ShaderResourceDeclaration *FindResourceDeclaration(std::string_view name) const;

    private:
        std::string m_Name;
        WeakRef<Shader> m_Shader;
        std::vector<WeakRef<Texture>> m_Textures;
        Ref<Buffer> m_UniformStorageBuffer;

        uint32_t offset = 0;
    };

}