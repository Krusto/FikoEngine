#pragma once
#include <unordered_map>
#include <entt/entt.hpp>
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Renderer/Viewport.h>
#include <Renderer/Shader.h>
#include <Renderer/Material.h>

class Entity;

class Scene{
public:
	Scene();

	void OnUpdate(float dt);
	
	Entity AddEntity(std::string name = "Unnamed");
	Entity CreateEntity(std::string name = "Unnamed");
	Entity RemoveEntity(UUID uuid);
	Entity RemoveEntity(Entity entity);

	auto data() { return m_Registry.data(); }

	Entity GetHandle();

	template <typename ...Component>
	auto GetEntitiesWith() {
		return m_Registry.view<Component...>();
	}

	auto HasUUID(UUID uuid) {
		return m_EntityMap.contains(uuid);
	}
	Entity GetEntity(UUID uuid);
	Entity FindEntity(const std::string& name);

	Entity GetSelectedEntity();
	Entity SetSelectedEntity(const Entity& entity);

	auto GetID() { return m_SceneID; }
	ViewportSize GetViewport() { return { m_ViewportWidth,m_ViewportHeight }; }

	Ref<Material> GetMaterial(std::string_view name);
	void AddMaterial(Ref<Material> material);

	Ref<Shader> GetShader(std::string_view name);
	void AddShader(std::string_view name, Ref<Shader> shader);

	auto& GetMaterials() { return m_MaterialLibrary; }
	auto& GetShaders() { return m_ShaderLibrary; }
private:
	entt::entity m_SceneEntity;
	entt::entity m_SelectedEntity{};
	UUID m_SceneID;

	std::unordered_map<UUID,Entity> m_EntityMap;

	entt::registry m_Registry;
	uint32_t m_ViewportWidth, m_ViewportHeight;

	std::unordered_map<std::string, Ref<Material>> m_MaterialLibrary;
	std::unordered_map<std::string, Ref<Shader>> m_ShaderLibrary;

	friend class Entity;
};