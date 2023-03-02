#pragma once
#include <Core/Ref.h>
#include <Core/Buffer.h>
#include <Core/UUID.h>
#include <Renderer/Shader.h>
#include "Texture.h"

namespace FikoEngine {
    class Material : public RefCounted {
    public:
        Material() = default;

        static Ref<Material> Create(const Ref<Shader> &shader, const std::string &name = "");

        virtual void Set(const std::string &name, float value) = 0;

        virtual void Set(const std::string &name, int value) = 0;

        virtual void Set(const std::string &name, u32 value) = 0;

        virtual void Set(const std::string &name, bool value) = 0;

        virtual void Set(const std::string &name, const glm::vec2 &value) = 0;

        virtual void Set(const std::string &name, const glm::vec3 &value) = 0;

        virtual void Set(const std::string &name, const glm::vec4 &value) = 0;

        virtual void Set(const std::string &name, const glm::ivec2 &value) = 0;

        virtual void Set(const std::string &name, const glm::ivec3 &value) = 0;

        virtual void Set(const std::string &name, const glm::ivec4 &value) = 0;

        virtual void Set(const std::string &name, const glm::mat3 &value) = 0;

        virtual void Set(const std::string &name, const glm::mat4 &value) = 0;

        virtual void Set(const std::string& name, const Ref<Texture>& texture) = 0;

        virtual void Set(const std::string& name, const Ref<Texture>& texture, u32 arrayIndex) = 0;

        virtual float &GetFloat(const std::string &name) = 0;

        virtual int32_t &GetInt(const std::string &name) = 0;

        virtual u32 &GetUInt(const std::string &name) = 0;

        virtual bool &GetBool(const std::string &name) = 0;

        virtual glm::vec2 &GetVector2(const std::string &name) = 0;

        virtual glm::vec3 &GetVector3(const std::string &name) = 0;

        virtual glm::vec4 &GetVector4(const std::string &name) = 0;

        virtual glm::mat3 &GetMatrix3(const std::string &name) = 0;

        virtual glm::mat4 &GetMatrix4(const std::string &name) = 0;

        virtual Ref<Texture> GetTexture(const std::string& name) = 0;

        virtual Ref<Texture> TryGetTexture(const std::string& name) = 0;

        virtual Ref<Shader> GetShader() = 0;

        virtual void SetShader(Ref<Shader> shader) = 0;

        virtual const std::string &GetName() const = 0;

        virtual void UpdateForRendering() = 0;

        virtual Buffer &GetBuffer() = 0;

        virtual void Reset() = 0;

        virtual bool HasDiffuseTexture() = 0;
        
        virtual bool HasSpecularTexture() = 0;

    };
}