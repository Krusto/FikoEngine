#include "Scene.h"
#include <string>
#include <unordered_map>
#include <Scene/Entity.h>
#include <Scene/Component.h>
#include <Core/UUID.h>
namespace FikoEngine {

    Scene::Scene() {
        m_SceneEntity = m_Registry.create();
        GetHandle().AddComponent<IDComponent>();
        GetHandle().GetComponent<IDComponent>().ID = m_SceneID;
        GetHandle().AddComponent<RelationshipComponent>();
        GetHandle().AddComponent<TagComponent>();
        GetHandle().GetComponent<TagComponent>().Tag = "Scene";

    }

    void Scene::OnUpdate(float dt) {
    }

    Entity Scene::AddEntity(std::string name) {
        Entity entity = Entity{m_Registry.create(), this};
        entity.AddComponent<IDComponent>();
        entity.AddComponent<TagComponent>();
        entity.AddComponent<RelationshipComponent>();

        UUID id;
        entity.GetComponent<IDComponent>().ID = id;
        entity.GetComponent<TagComponent>().Tag = name;

        entity.GetComponent<RelationshipComponent>().ParentHandle = m_SceneID;

        GetHandle().AddChild(entity);
        m_EntityMap.emplace(std::pair(id, Ref<Entity>::Create(entity)));
        return entity;
    }

    Entity Scene::CreateEntity(std::string name) {
        Entity entity = Entity{m_Registry.create(), this};
        entity.AddComponent<IDComponent>();
        entity.AddComponent<TagComponent>();
        entity.AddComponent<RelationshipComponent>();

        UUID id;
        entity.GetComponent<IDComponent>().ID = id;
        entity.GetComponent<TagComponent>().Tag = name;

        m_EntityMap.emplace(std::pair(id, Ref<Entity>::Create(entity)));
        return entity;
    }

    Entity Scene::RemoveEntity(UUID uuid) {
        if (HasUUID(uuid)) {
            m_Registry.destroy(*(m_EntityMap[uuid].Raw()));
            m_EntityMap.erase(uuid);
        }
        return {m_SceneEntity, this};
    }

    Entity Scene::RemoveEntity(Entity entity) {
        auto uuid = entity.GetUUID();
        if (HasUUID(uuid)) {
            m_Registry.destroy(*(m_EntityMap[uuid].Raw()));
            m_EntityMap.erase(uuid);
        }
        return {m_SceneEntity, this};
    }

    Entity Scene::GetHandle() {
        return {(u32) m_SceneEntity, this};
    }

    Entity Scene::GetEntity(UUID uuid) {
        if (m_EntityMap.contains(uuid))
            return *m_EntityMap.at(uuid).Raw();
        return Entity{(u32) entt::null, this};
    }

    Entity Scene::FindEntity(const std::string &name) {
        for (auto&[uuid, entity]: m_EntityMap) {
            if ((*entity.Raw()).HasComponent<TagComponent>()) {
                if ((*entity.Raw()).GetComponent<TagComponent>().Tag == name) {
                    return *entity.Raw();
                }
            }
        }
        return {(u32) m_SceneEntity, this};
    }

    Entity Scene::GetSelectedEntity() {
        if (m_SelectedEntity != entt::null)
            return Entity{(u32) m_SelectedEntity, this};
        return {(u32) entt::null, this};
    }

    Entity Scene::SetSelectedEntity(const Entity &entity) {
        m_SelectedEntity = (entt::entity) entity;
        return GetHandle();
    }

    Ref<Material> Scene::GetMaterial(std::string_view name) {
        return m_MaterialLibrary.at(name.data());
    }

    void Scene::AddMaterial(Ref<Material> material) {
        m_MaterialLibrary.try_emplace(material->GetName(), material);
    }

    Ref<Shader> Scene::GetShader(std::string_view name) {
        return m_ShaderLibrary.at(name.data());
    }

    void Scene::AddShader(std::string_view name, Ref<Shader> shader) {
        m_ShaderLibrary.try_emplace(std::string(name), shader);
    }

    Ref<Texture> Scene::GetTexture(std::string_view name)
    {
        if(m_TextureLibrary.contains(name.data()))
            return m_TextureLibrary.at(name.data());
        return Ref<Texture>();
    }

    void Scene::AddTexture(std::string_view name, Ref<Texture> texture)
    {
        m_TextureLibrary.try_emplace(std::string(name), texture);
    }

    void Scene::RemoveTexture(std::string_view name)
    {
        GetTexture(name)->Destroy();
    }
}