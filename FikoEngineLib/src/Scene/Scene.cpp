#include "Scene.h"
#include <string>
#include <Scene/Entity.h>
#include <Scene/Component.h>
#include <Scene/SceneSerializer.hpp>
#include <Core/UUID.h>

namespace FikoEngine {

    Scene::Scene(std::string_view name, std::string_view fileLocation) {
        m_SelectedEntity = entt::null;
        m_SceneEntity = m_Registry.create();
        GetHandle().AddComponents<IDComponent,RelationshipComponent,TagComponent,FileComponent>();
        GetHandle().GetComponent<IDComponent>().ID = m_SceneID;
        GetHandle().GetComponent<TagComponent>().Tag = name;
        GetHandle().GetComponent<FileComponent>().Path = fileLocation;
    }

    void Scene::OnUpdate(float dt) {
        (void)dt;
    }

    Entity Scene::AddEntity(std::string name) {
        UUID id;
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<IDComponent>();
        entity.AddComponent<TagComponent>();
        entity.AddComponent<RelationshipComponent>();

        entity.GetComponent<IDComponent>().ID = id;
        entity.GetComponent<TagComponent>().Tag = std::move(name);
        entity.GetComponent<RelationshipComponent>().ParentHandle = m_SceneID;

        GetHandle().GetComponent<RelationshipComponent>().AddChild(id);

        m_EntityMap.emplace(std::pair(id, entity));
        return entity;
    }
    Entity Scene::AddEntity(Entity entity) {
        if(entity.IsValid() && entity.HasComponent<IDComponent>() && entity.HasComponent<RelationshipComponent>()) {
            m_EntityMap.emplace(std::pair(entity.GetComponent<IDComponent>().ID, entity));
            GetHandle().GetComponent<RelationshipComponent>().Children.push_back(entity.GetComponent<IDComponent>().ID);
        }
        return entity;
    }
    Entity Scene::CreateEmptyEntity() {
        Entity entity = {m_Registry.create(),this};
        return entity;
    }

    Entity Scene::CreateEntity(std::string name) {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<IDComponent>();
        entity.AddComponent<TagComponent>();
        entity.AddComponent<RelationshipComponent>();

        UUID id;
        entity.GetComponent<IDComponent>().ID = id;
        entity.GetComponent<TagComponent>().Tag = std::move(name);

        m_EntityMap.emplace(std::pair(id, entity));
        return entity;
    }

    Entity Scene::RemoveEntity(const UUID& uuid) {
        if (HasUUID(uuid)) {
            m_Registry.destroy(m_EntityMap[uuid].m_EntityHandle);
            m_EntityMap.erase(uuid);
        }
        return GetHandle();
    }

    Entity Scene::RemoveEntity(Entity entity) {
        auto uuid = entity.GetUUID();
        if (HasUUID(uuid)) {
            m_Registry.destroy(m_EntityMap[uuid].m_EntityHandle);
            m_EntityMap.erase(uuid);
        }
        return GetHandle();
    }

    Entity Scene::GetHandle() {
        return {m_SceneEntity,this};
    }

    Entity Scene::GetEntity(const UUID& uuid) {
        if (m_EntityMap.contains(uuid))
            return m_EntityMap.at(uuid);
        return {(uint32_t)entt::null,nullptr};
    }

    Entity Scene::FindEntity(const std::string &name) {
        for (auto&[uuid, entity]: m_EntityMap) {
            if (entity.HasComponent<TagComponent>()) {
                if (entity.GetComponent<TagComponent>().Tag == name) {
                    return entity;
                }
            }
        }
        return GetHandle();
    }

    Entity Scene::GetSelectedEntity() {
        if (m_SelectedEntity != entt::null)
            return {m_SelectedEntity,this};
        return {(uint32_t)entt::null,nullptr};
    }

    Entity Scene::SetSelectedEntity(const Entity& entity) {
        m_SelectedEntity = entity.m_EntityHandle;
        return GetHandle();
    }

    WeakRef<Material> Scene::GetMaterial(std::string_view name) {
        if(m_MaterialLibrary.contains(std::string(name)))
            return m_MaterialLibrary.at(std::string(name));
        return {};
    }

    void Scene::AddMaterial(std::string_view materialName, std::string_view shaderName) {
        if(!m_MaterialLibrary.contains(std::string(materialName))) {
            m_MaterialLibrary.try_emplace(std::string(materialName), Ref<Material>(Material::Create(GetShader(shaderName), std::string(materialName))));
            return;
        }

        LOG_WARNING("Material " + std::string(materialName) + " already exists!");
    }

    WeakRef<Shader> Scene::GetShader(std::string_view name) {
        if(m_ShaderLibrary.contains(std::string(name)))
            return m_ShaderLibrary.at(std::string(name));
        LOG_WARNING("Cannot find " + std::string(name) + " shader from the library!")
        return {};
    }

    void Scene::AddShader(std::string_view name, std::string_view path) {
        auto [iter,status] = m_ShaderLibrary.try_emplace(std::string(name), Shader::Load(path.data()));
        if(!status)
            LOG_ERROR("Cannot add " + std::string(name) + " shader to the library!");
    }

    WeakRef<Texture> Scene::GetTexture(std::string_view name)
    {
        if(m_TextureLibrary.contains(name.data()))
            return m_TextureLibrary.at(name.data());
        return {};
    }

    void Scene::AddTexture(std::string_view name, std::string_view path)
    {
        auto [iter,status] = m_TextureLibrary.try_emplace(std::string(name), Texture::Create(path));
        if(!status)
            LOG_ERROR("Texture " + std::string(name) + " already exists!");
    }

    void Scene::RemoveTexture(std::string_view name)
    {
        auto texture = GetTexture(name).Lock();
        if(texture) {
            texture->Destroy();
            m_TextureLibrary.at(std::string(name)).Reset();
            m_TextureLibrary.erase(std::string(name));
            return;
        }
        LOG_WARNING("Texture " + std::string(name) + " does not exist!");
    }

    Scene::~Scene() {
        Destroy();
    }
    void Scene::Destroy() {
        LOG_INFO("Destroying scene");
        LOG_INFO("Destroying textures");
        for(auto& [name,texture] : m_TextureLibrary){
            texture->Destroy();
            texture.Reset();
        }
        m_TextureLibrary.clear();
        LOG_INFO("Destroying materials");
        for(auto& [name,material] : m_MaterialLibrary){
            material.Reset();
        }
        m_MaterialLibrary.clear();
    }

    bool Scene::HasUUID(const UUID &uuid) {
        return m_EntityMap.contains(uuid);
    }

}