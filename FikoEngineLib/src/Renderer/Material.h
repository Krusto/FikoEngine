#pragma once
#include <Core/Ref.h>
#include <Core/Buffer.h>
#include <Core/UUID.h>
#include <Renderer/Shader.h>
#include "Texture.h"

namespace FikoEngine {
    class Material : public RefCounted{
    public:
        Material() = default;
        static Material* Create(WeakRef<Shader> shader, std::string_view name);

        virtual ~Material() {LOG_INFO("Destroying Material")};

        virtual void Set(std::string_view name, float value) = 0;

        virtual void Set(std::string_view name, int value) = 0;

        virtual void Set(std::string_view name, uint32_t value) = 0;

        virtual void Set(std::string_view name, bool value) = 0;

        virtual void Set(std::string_view name, const glm::vec2 &value) = 0;

        virtual void Set(std::string_view name, const glm::vec3 &value) = 0;

        virtual void Set(std::string_view name, const glm::vec4 &value) = 0;

        virtual void Set(std::string_view name, const glm::ivec2 &value) = 0;

        virtual void Set(std::string_view name, const glm::ivec3 &value) = 0;

        virtual void Set(std::string_view name, const glm::ivec4 &value) = 0;

        virtual void Set(std::string_view name, const glm::mat3 &value) = 0;

        virtual void Set(std::string_view name, const glm::mat4 &value) = 0;

        virtual void Set(std::string_view name, WeakRef<Texture> texture) = 0;

        virtual void Set(std::string_view name, WeakRef<Texture> texture, uint32_t arrayIndex) = 0;

        virtual float &GetFloat(std::string_view name) = 0;

        virtual int32_t &GetInt(std::string_view name) = 0;

        virtual uint32_t &GetUInt(std::string_view name) = 0;

        virtual bool &GetBool(std::string_view name) = 0;

        virtual glm::vec2 &GetVector2(std::string_view name) = 0;

        virtual glm::vec3 &GetVector3(std::string_view name) = 0;

        virtual glm::vec4 &GetVector4(std::string_view name) = 0;

        virtual glm::mat3 &GetMatrix3(std::string_view name) = 0;

        virtual glm::mat4 &GetMatrix4(std::string_view name) = 0;

        virtual WeakRef<Texture> GetTexture(std::string_view name) = 0;

        virtual WeakRef<Texture> TryGetTexture(std::string_view name) = 0;

        virtual WeakRef<Shader> GetShader() = 0;

        virtual WeakRef<Shader> GetShader() const = 0;

        virtual const float &GetFloat(std::string_view name) const = 0;

        virtual const int32_t &GetInt(std::string_view name) const = 0;

        virtual const uint32_t &GetUInt(std::string_view name) const = 0;

        virtual const bool &GetBool(std::string_view name) const = 0;

        virtual const glm::vec2 &GetVector2(std::string_view name) const = 0;

        virtual const glm::vec3 &GetVector3(std::string_view name) const = 0;

        virtual const glm::vec4 &GetVector4(std::string_view name) const = 0;

        virtual const glm::mat3 &GetMatrix3(std::string_view name) const = 0;

        virtual const glm::mat4 &GetMatrix4(std::string_view name) const = 0;

        virtual WeakRef<Texture> GetTexture(std::string_view name) const = 0;

        virtual WeakRef<Texture> TryGetTexture(std::string_view name) const = 0;

        virtual void SetShader(WeakRef<Shader> shader) = 0;

        virtual std::string_view GetName() const = 0;

        virtual void UpdateForRendering() = 0;

        virtual Buffer &GetBuffer() = 0;

        virtual void Reset() = 0;

        virtual bool HasDiffuseTexture() = 0;
        
        virtual bool HasSpecularTexture() = 0;

    };
}