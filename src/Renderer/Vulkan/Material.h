#pragma once

#include <map>
#include <Core/Buffer.h>
#include <Renderer/Material.h>
#include <Renderer/Texture.h>

class OpenGLMaterial : public Material
{
public:
	OpenGLMaterial(const Ref<Shader>& shader, const std::string& name = "");

	virtual void Set(const std::string& name, float value) override;
	virtual void Set(const std::string& name, int value) override;
	virtual void Set(const std::string& name, uint32_t value) override;
	virtual void Set(const std::string& name, bool value) override;
	virtual void Set(const std::string& name, const glm::ivec2& value) override;
	virtual void Set(const std::string& name, const glm::ivec3& value) override;
	virtual void Set(const std::string& name, const glm::ivec4& value) override;

	virtual void Set(const std::string& name, const glm::vec2& value) override;
	virtual void Set(const std::string& name, const glm::vec3& value) override;
	virtual void Set(const std::string& name, const glm::vec4& value) override;
	virtual void Set(const std::string& name, const glm::mat3& value) override;
	virtual void Set(const std::string& name, const glm::mat4& value) override;

	virtual void Set(const std::string& name, const Ref<Texture>& texture) override;
	virtual void Set(const std::string& name, const Ref<Texture>& texture, uint32_t arrayIndex) override {}

	virtual float& GetFloat(const std::string& name) override;
	virtual int32_t& GetInt(const std::string& name) override;
	virtual uint32_t& GetUInt(const std::string& name) override;
	virtual bool& GetBool(const std::string& name) override;
	virtual glm::vec2& GetVector2(const std::string& name) override;
	virtual glm::vec3& GetVector3(const std::string& name) override;
	virtual glm::vec4& GetVector4(const std::string& name) override;
	virtual glm::mat3& GetMatrix3(const std::string& name) override;
	virtual glm::mat4& GetMatrix4(const std::string& name) override;

	virtual Ref<Texture> GetTexture(const std::string& name) override;
	virtual Ref<Texture> TryGetTexture(const std::string& name) override;

	template <typename T>
	void Set(const std::string& name, const T& value,ShaderUniformType type,uint32_t size)
	{
		auto& shaderBuffer = m_Shader->GetShaderBuffers()["shaderBuffer"];
		shaderBuffer.Size += 1;

		std::string uniformName = name;
		auto& uniform  = shaderBuffer.Uniforms[name];
		uniform.m_Name = uniformName;
		uniform.m_Offset = m_Shader->offset;
		uniform.m_Size = size;
		uniform.m_Type = type;

		auto& buffer = m_UniformStorageBuffer;

		buffer.Write((byte*)&value, size,m_Shader->offset);
		m_Shader->offset += size;
	}

	template<typename T>
	T& Get(const std::string& name)
	{
		auto decl = FindUniformDeclaration(name);
		assert(decl);
//			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
		auto& buffer = m_UniformStorageBuffer;
		return buffer.Read<T>(decl->GetOffset());
	}

	template<typename T>
	Ref<T> GetResource(const std::string& name)
	{
		return {};
	}

	template<typename T>
	Ref<T> TryGetResource(const std::string& name)
	{
		return {};
	}

	virtual Ref<Shader> GetShader() override { return m_Shader; }
	virtual const std::string& GetName() const override { return m_Name; }

	Buffer GetUniformStorageBuffer() { return m_UniformStorageBuffer; }

	virtual void UpdateForRendering() override;

	virtual Buffer& GetBuffer() override { return m_UniformStorageBuffer; };

private:
	void AllocateStorage();
	void OnShaderReloaded();

	const ShaderUniform* FindUniformDeclaration(const std::string& name);
	const ShaderResourceDeclaration* FindResourceDeclaration(const std::string& name);
private:
	Ref<Shader> m_Shader;
	std::string m_Name;

	uint32_t m_MaterialFlags = 0;
	uint32_t offset = 0;

	Buffer m_UniformStorageBuffer;
	std::vector<Ref<Texture>> m_Textures;
};

