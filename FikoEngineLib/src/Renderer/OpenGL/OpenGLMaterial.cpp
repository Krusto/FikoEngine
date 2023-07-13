#include "OpenGLMaterial.h"
#include <Renderer/Shader.h>
#include <iostream>
#include <Renderer\OpenGL\OpenGLShader.h>
#include <Renderer/OpenGL/OpenGLTexture.h>

namespace FikoEngine {

    OpenGLMaterial::OpenGLMaterial(WeakRef<Shader> shader,std::string_view name)
            : m_Shader(shader), m_Name(name) {
        AllocateStorage();
    }

    OpenGLMaterial::OpenGLMaterial(std::string_view name)
            : m_Name(name) {
        AllocateStorage();
    }


    void OpenGLMaterial::AllocateStorage() {
        //const auto& shaderBuffers = m_Shader->GetShaderBuffers();

        //if (shaderBuffers.size() > 0)
        //{
        //	uint32_t size = 0;
        //	for (auto& [name, shaderBuffer] : shaderBuffers)
        //		size += shaderBuffer.Size;
        m_UniformStorageBuffer = Ref<Buffer>::Create();
        m_UniformStorageBuffer->Allocate(2048); //fix this
        m_UniformStorageBuffer->ZeroInitialize();
        //}
    }

    void OpenGLMaterial::OnShaderReloaded() {
        return;
        AllocateStorage();
    }

    const ShaderUniform *OpenGLMaterial::FindUniformDeclaration(std::string_view name) {
        if(m_Shader.IsValid()) {
            const auto &shader = m_Shader.Lock();
            const auto &shaderBuffers = shader->GetShaderBuffers();

            assert(shaderBuffers.size() <= 1);//"We currently only support ONE material buffer!");

            if (shaderBuffers.size() > 0) {
                const ShaderBuffer &buffer = (*shaderBuffers.begin()).second;
                if (buffer.Uniforms.find(std::string(name)) == buffer.Uniforms.end())
                    return nullptr;

                return &buffer.Uniforms.at(std::string(name));
            }
        }
        return nullptr;
    }

    const ShaderUniform *OpenGLMaterial::FindUniformDeclaration(std::string_view name) const{
        if(m_Shader.IsValid()) {
            const auto &shader = m_Shader.Lock();
            const auto &shaderBuffers = shader->GetShaderBuffers();

            assert(shaderBuffers.size() <= 1);//"We currently only support ONE material buffer!");

            if (shaderBuffers.size() > 0) {
                const ShaderBuffer &buffer = (*shaderBuffers.begin()).second;
                if (buffer.Uniforms.find(std::string(name)) == buffer.Uniforms.end())
                    return nullptr;

                return &buffer.Uniforms.at(std::string(name));
            }
        }
        return nullptr;
    }

    const ShaderResourceDeclaration *OpenGLMaterial::FindResourceDeclaration(std::string_view name) {
        if(m_Shader.IsValid()) {
            const auto &shader = m_Shader.Lock();
            auto &resources = shader->GetResources();
            for (const auto &[n, resource]: resources) {
                if (resource.GetName() == name)
                    return &resource;
            }
        }
        return nullptr;
    }
    const ShaderResourceDeclaration *OpenGLMaterial::FindResourceDeclaration(std::string_view name) const {
        if(m_Shader.IsValid()) {
            const auto &shader = m_Shader.Lock();
            auto &resources = shader->GetResources();
            for (const auto &[n, resource]: resources) {
                if (resource.GetName() == name)
                    return &resource;
            }
        }
        return nullptr;
    }

    void OpenGLMaterial::Set(std::string_view name, float value) {
        Set<float>(name, value, ShaderUniformType::Float, sizeof(float));
    }

    void OpenGLMaterial::Set(std::string_view name, int value) {
        Set<int>(name, value, ShaderUniformType::Int, sizeof(int));
    }

    void OpenGLMaterial::Set(std::string_view name, uint32_t value) {
        Set<uint32_t>(name, value, ShaderUniformType::UInt, sizeof(uint32_t));
    }

    void OpenGLMaterial::Set(std::string_view name, bool value) {
        // Bools are uints
        Set<uint32_t>(name, (int) value, ShaderUniformType::UInt, sizeof(uint32_t));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::ivec2 &value) {
        Set<glm::ivec2>(name, value, ShaderUniformType::IVec2, sizeof(glm::ivec2));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::ivec3 &value) {
        Set<glm::ivec3>(name, value, ShaderUniformType::IVec3, sizeof(glm::ivec3));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::ivec4 &value) {
        Set<glm::ivec4>(name, value, ShaderUniformType::IVec4, sizeof(glm::ivec4));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::vec2 &value) {
        Set<glm::vec2>(name, value, ShaderUniformType::Vec2, sizeof(glm::vec2));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::vec3 &value) {
        Set<glm::vec3>(name, value, ShaderUniformType::Vec3, sizeof(glm::vec3));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::vec4 &value) {
        Set<glm::vec4>(name, value, ShaderUniformType::Vec4, sizeof(glm::vec4));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::mat3 &value) {
        Set<glm::mat3>(name, value, ShaderUniformType::Mat3, sizeof(glm::mat3));
    }

    void OpenGLMaterial::Set(std::string_view name, const glm::mat4 &value) {
        Set<glm::mat4>(name, value, ShaderUniformType::Mat4, sizeof(glm::mat4));
    }

    void OpenGLMaterial::Set(std::string_view name, WeakRef<Texture> texture) {
        auto decl = FindResourceDeclaration(name);
        if (!decl) {
            assert(0);
            //				HZ_CORE_WARN("Cannot find material property: ", name);
            return;
        }
        uint32_t slot = decl->GetRegister();
        if (m_Textures.size() <= slot)
            m_Textures.resize((size_t) slot + 1);

        m_Textures[slot] = texture;
    }
    void OpenGLMaterial::Set(std::string_view name, WeakRef<Texture> texture, uint32_t arrayIndex) {
        if (m_Textures.size() > arrayIndex)
            m_Textures[arrayIndex] = texture;
    }

    float &OpenGLMaterial::GetFloat(std::string_view name) {
        return Get<float>(name);
    }

    int32_t &OpenGLMaterial::GetInt(std::string_view name) {
        return Get<int32_t>(name);
    }

    uint32_t &OpenGLMaterial::GetUInt(std::string_view name) {
        return Get<uint32_t>(name);
    }

    bool &OpenGLMaterial::GetBool(std::string_view name) {
        return Get<bool>(name);
    }

    glm::vec2 &OpenGLMaterial::GetVector2(std::string_view name) {
        return Get<glm::vec2>(name);
    }

    glm::vec3 &OpenGLMaterial::GetVector3(std::string_view name) {
        return Get<glm::vec3>(name);
    }

    glm::vec4 &OpenGLMaterial::GetVector4(std::string_view name) {
        return Get<glm::vec4>(name);
    }

    glm::mat3 &OpenGLMaterial::GetMatrix3(std::string_view name) {
        return Get<glm::mat3>(name);
    }

    glm::mat4 &OpenGLMaterial::GetMatrix4(std::string_view name) {
        return Get<glm::mat4>(name);
    }

    WeakRef<Texture> OpenGLMaterial::GetTexture(std::string_view name) {
        auto decl = FindResourceDeclaration(name);
        assert(decl);// "Could not find uniform with name 'x'");
        uint32_t slot = decl->GetRegister();
        assert((slot < m_Textures.size()));// "Texture slot is invalid");
        return m_Textures[slot];
    }

    WeakRef<Texture> OpenGLMaterial::TryGetTexture(std::string_view name) {
        return TryGetResource<Texture>(name);
    }

    const float &OpenGLMaterial::GetFloat(std::string_view name) const {
        return Get<float>(name);
    }

    const int32_t &OpenGLMaterial::GetInt(std::string_view name) const {
        return Get<int32_t>(name);
    }

    const uint32_t &OpenGLMaterial::GetUInt(std::string_view name) const {
        return Get<uint32_t>(name);
    }

    const bool &OpenGLMaterial::GetBool(std::string_view name) const {
        return Get<bool>(name);
    }

    const glm::vec2 &OpenGLMaterial::GetVector2(std::string_view name) const {
        return Get<glm::vec2>(name);
    }

    const glm::vec3 &OpenGLMaterial::GetVector3(std::string_view name) const {
        return Get<glm::vec3>(name);
    }

    const glm::vec4 &OpenGLMaterial::GetVector4(std::string_view name) const {
        return Get<glm::vec4>(name);
    }

    const glm::mat3 &OpenGLMaterial::GetMatrix3(std::string_view name) const {
        return Get<glm::mat3>(name);
    }

    const glm::mat4 &OpenGLMaterial::GetMatrix4(std::string_view name) const {
        return Get<glm::mat4>(name);
    }

    WeakRef<Texture> OpenGLMaterial::GetTexture(std::string_view name) const {
        auto decl = FindResourceDeclaration(name);
        assert(decl);// "Could not find uniform with name 'x'");
        uint32_t slot = decl->GetRegister();
        assert((slot < m_Textures.size()));// "Texture slot is invalid");
        return m_Textures[slot];
    }

    WeakRef<Texture> OpenGLMaterial::TryGetTexture(std::string_view name) const {
        return TryGetResource<Texture>(name);
    }

    void OpenGLMaterial::UpdateForRendering() {
        if(m_Shader.IsValid()) {
            Ref<OpenGLShader> shader = m_Shader.Lock().As<OpenGLShader>();
            shader->Bind();
            const auto &shaderBuffers = shader->GetShaderBuffers();
            assert(shaderBuffers.size() <= 1);// "We currently only support ONE material buffer!");

            if (shaderBuffers.size() > 0) {
                const ShaderBuffer &buffer = (*shaderBuffers.begin()).second;

                for (auto &[name, uniform]: buffer.Uniforms) {
                    switch (uniform.GetType()) {
                        case ShaderUniformType::Bool:
                        case ShaderUniformType::UInt: {
                            const uint32_t value = m_UniformStorageBuffer->Read<uint32_t>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Int: {
                            const int value = m_UniformStorageBuffer->Read<int>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::IVec2: {
                            const glm::ivec2 &value = m_UniformStorageBuffer->Read<glm::ivec2>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::IVec3: {
                            const glm::ivec3 &value = m_UniformStorageBuffer->Read<glm::ivec3>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::IVec4: {
                            const glm::ivec4 &value = m_UniformStorageBuffer->Read<glm::ivec4>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Float: {
                            const float value = m_UniformStorageBuffer->Read<float>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Vec2: {
                            const glm::vec2 &value = m_UniformStorageBuffer->Read<glm::vec2>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Vec3: {
                            const glm::vec3 &value = m_UniformStorageBuffer->Read<glm::vec3>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Vec4: {
                            const glm::vec4 &value = m_UniformStorageBuffer->Read<glm::vec4>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Mat3: {
                            const glm::mat3 &value = m_UniformStorageBuffer->Read<glm::mat3>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        case ShaderUniformType::Mat4: {
                            const glm::mat4 &value = m_UniformStorageBuffer->Read<glm::mat4>(uniform.GetOffset());
                            shader->SetUniform(name, value);
                            break;
                        }
                        default: {
                            assert(false);
                            break;
                        }
                    }
                }
            }
            for (size_t i = 0; i < m_Textures.size(); i++) {
                auto texture = m_Textures[i].Lock();
                if (texture) {
                    assert(texture->GetType() == TextureType::Texture2D);
                    texture->Bind(i);
                }
            }
        }
    }

    bool OpenGLMaterial::HasDiffuseTexture() {
        return FindResourceDeclaration("Diffuse") != nullptr;
    }
    bool OpenGLMaterial::HasSpecularTexture() {
        return FindResourceDeclaration("Specular") != nullptr;
    }

    OpenGLMaterial::~OpenGLMaterial() {
        LOG_INFO("DEStroying OPENGL MATERIAL")
    }

}