#pragma once

#include <map>
#include <Core/Buffer.h>
#include <Renderer/Material.h>

namespace FikoEngine {
    class VulkanMaterial : public Material {
    public:
        VulkanMaterial(WeakRef<Shader> shader, std::string_view name);

        virtual void Set(std::string_view name, float value) override;

        virtual void Set(std::string_view name, int value) override;

        virtual void Set(std::string_view name, uint32_t value) override;

        virtual void Set(std::string_view name, bool value) override;

        virtual void Set(std::string_view name, const glm::ivec2 &value) override;

        virtual void Set(std::string_view name, const glm::ivec3 &value) override;

        virtual void Set(std::string_view name, const glm::ivec4 &value) override;

        virtual void Set(std::string_view name, const glm::vec2 &value) override;

        virtual void Set(std::string_view name, const glm::vec3 &value) override;

        virtual void Set(std::string_view name, const glm::vec4 &value) override;

        virtual void Set(std::string_view name, const glm::mat3 &value) override;

        virtual void Set(std::string_view name, const glm::mat4 &value) override;

        virtual float &GetFloat(std::string_view name) override;

        virtual int32_t &GetInt(std::string_view name) override;

        virtual uint32_t &GetUInt(std::string_view name) override;

        virtual bool &GetBool(std::string_view name) override;

        virtual glm::vec2 &GetVector2(std::string_view name) override;

        virtual glm::vec3 &GetVector3(std::string_view name) override;

        virtual glm::vec4 &GetVector4(std::string_view name) override;

        virtual glm::mat3 &GetMatrix3(std::string_view name) override;

        virtual glm::mat4 &GetMatrix4(std::string_view name) override;


        virtual const float &GetFloat(std::string_view name) const override;

        virtual const int32_t &GetInt(std::string_view name) const override;

        virtual const uint32_t &GetUInt(std::string_view name) const override;

        virtual const bool &GetBool(std::string_view name) const override;

        virtual const glm::vec2 &GetVector2(std::string_view name) const override;

        virtual const glm::vec3 &GetVector3(std::string_view name) const override;

        virtual const glm::vec4 &GetVector4(std::string_view name) const override;

        virtual const glm::mat3 &GetMatrix3(std::string_view name) const override;

        virtual const glm::mat4 &GetMatrix4(std::string_view name) const override;

        virtual void Set(std::string_view name, WeakRef<Texture> texture) override{}
        virtual void Set(std::string_view name, WeakRef<Texture> texture, uint32_t arrayIndex) override{}

        virtual WeakRef<Texture> GetTexture(std::string_view name) override;
        virtual WeakRef<Texture> TryGetTexture(std::string_view name) override;
        virtual WeakRef<Texture> GetTexture(std::string_view name) const override;
        virtual WeakRef<Texture> TryGetTexture(std::string_view name) const override;

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

                buffer.Write((byte *) &value, size, shader->offset);
                shader->offset += size;
            }
        }

        template<typename T>
        T &Get(std::string_view name) {
            auto decl = FindUniformDeclaration(name);
            assert(decl);
//			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
            auto &buffer = m_UniformStorageBuffer;
            return buffer.Read<T>(decl->GetOffset());
        }

        template<typename T>
        T &Get(std::string_view name) const{
            auto decl = FindUniformDeclaration(name);
            assert(decl);
//			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
            auto &buffer = m_UniformStorageBuffer;
            return buffer.Read<T>(decl->GetOffset());
        }

        template<typename T>
        Ref<T> GetResource(std::string_view name) {
            return {};
        }

        template<typename T>
        Ref<T> TryGetResource(std::string_view name) {
            return {};
        }

        template<typename T>
        Ref<T> TryGetResource(std::string_view name) const {
            return {};
        }

        virtual void SetShader(WeakRef<Shader> shader) override { m_Shader = shader;}
        virtual WeakRef<Shader> GetShader() override { return m_Shader; }
        virtual WeakRef<Shader> GetShader() const override { return m_Shader; }

        virtual std::string_view GetName() const override { return m_Name; }

        Buffer GetUniformStorageBuffer() { return m_UniformStorageBuffer; }

        virtual void UpdateForRendering() override;

        virtual Buffer &GetBuffer() override { return m_UniformStorageBuffer; }

        virtual void Reset() override {
            if(m_Shader.IsValid()) {
                auto shader = m_Shader.Lock();
                shader->Reload();
            }
        };

        virtual bool HasDiffuseTexture() override{return false;}

        virtual bool HasSpecularTexture() override{return false;}

    private:
        void AllocateStorage();

        void OnShaderReloaded();

        const ShaderUniform *FindUniformDeclaration(std::string_view name);
        const ShaderUniform *FindUniformDeclaration(std::string_view name) const;

        const ShaderResourceDeclaration *FindResourceDeclaration(std::string_view name);
        const ShaderResourceDeclaration *FindResourceDeclaration(std::string_view name) const;

    private:
        WeakRef<Shader> m_Shader;
        std::string m_Name;

        uint32_t m_MaterialFlags = 0;
        uint32_t offset = 0;

        Buffer m_UniformStorageBuffer;

        std::vector<WeakRef<Texture>> m_Textures;
    };
}

