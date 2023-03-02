#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <Core/Ref.h>
#include <Renderer/ShaderUniform.h>
#include "ShaderDataType.h"

namespace FikoEngine {
    enum class ShaderType {
        None,
        Vertex,
        Fragment,
        Compute,
        Other
    };

    class ShaderUniform {
    public:
        ShaderUniform() = default;

        ShaderUniform(std::string Name, const ShaderUniformType type, const u32 size, const u32 offset)
                : m_Name(std::move(Name)), m_Type(type), m_Size(size), m_Offset(offset) {}

        const auto &GetName() { return m_Name; }

        ShaderUniformType &GetType() { return m_Type; }

        const ShaderUniformType &GetType() const { return m_Type; }

        u32 GetSize() { return m_Size; }

        const u32 GetSize() const { return m_Size; }

        u32 GetOffset() { return m_Offset; }

        const u32 GetOffset() const { return m_Offset; }

        std::string_view m_Name{};
        ShaderUniformType m_Type{};
        u32 m_Size{};
        u32 m_Offset{};
    };

    struct ShaderUniformBuffer {
        std::string Name;
        u32 Index;
        u32 BindingPoint;
        u32 Size;
        u32 id;
        std::vector<ShaderUniform> Uniforms;
    };

    struct ShaderStorageBuffer {
        std::string Name;
        u32 Index;
        u32 BindingPoint;
        u32 Size;
        u32 id;
        //std::vector<ShaderUniform> Uniforms;
    };

    struct ShaderBuffer {
        std::string Name;
        u32 Size = 0;
        std::unordered_map<std::string, ShaderUniform> Uniforms;
    };

    class Shader : public RefCounted {
    public:

        static Ref<Shader> Load(const std::string &path);
        virtual std::unordered_map<std::string, ShaderBuffer> &GetShaderBuffers() = 0;
        virtual const std::unordered_map<std::string, ShaderResourceDeclaration> &GetResources() const = 0;
        virtual const std::string &GetName() const = 0;
        virtual const std::string &GetPath() const = 0;
        virtual void Reload(bool forceCompile = true) = 0;
        virtual void Bind() = 0;
        virtual void SetUniformBuffer(const std::string &name, const void *data, u32 size) = 0;
        virtual void SetStorageBuffer(const std::string &name, const void *data, u32 size) = 0;
        virtual void ResizeStorageBuffer(u32 bindingPoint, u32 newSize) = 0;
        virtual void SetUniform(const std::string &fullname, float value) = 0;
        virtual void SetUniform(const std::string &fullname, int value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::ivec2 &value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::ivec3 &value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::ivec4 &value) = 0;
        virtual void SetUniform(const std::string &fullname, u32 value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::vec2 &value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::vec3 &value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::vec4 &value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::mat3 &value) = 0;
        virtual void SetUniform(const std::string &fullname, const glm::mat4 &value) = 0;
        virtual void AddResource(std::string_view name, ShaderResourceDeclaration resource) = 0;
        u32 offset = 0;
    };

}