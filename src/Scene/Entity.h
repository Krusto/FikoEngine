#pragma once
#include <entt/entt.hpp>
#include <Scene/Component.h>
#include <Scene/Scene.h>
namespace FikoEngine {
    class Entity {
    public:
        Entity() = default;

        Entity(uint32_t entityHandle, Scene *scene) :
                m_EntityHandle((entt::entity) entityHandle), m_Scene(scene) {}

        Entity(entt::entity entityHandle, Scene *scene) :
                m_EntityHandle(entityHandle), m_Scene(scene) {}

        template<typename T>
        T &GetComponent() {
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        T &GetComponent() const {
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() {
            return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() const {
            return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent() {
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        template<typename...T>
        bool HasAny() {
            if (m_Scene != nullptr)
                return m_Scene->m_Registry.any_of<T...>(m_EntityHandle);
            return false;
        }

        template<typename...T>
        bool HasAny() const {
            return m_Scene->m_Registry.any_of<T...>(m_EntityHandle);
        }

        template<typename T>
        Entity AddComponent() {
            m_Scene->m_Registry.emplace<T>(m_EntityHandle);
            return *this;

        }

        template<typename ...T>
        Entity AddComponents() {
            m_Scene->m_Registry.emplace<T...>(m_EntityHandle);
            return *this;
        }

        bool HasParents() {
            return m_Scene->m_Registry.get<RelationshipComponent>(m_EntityHandle).ParentHandle != 0;
        }

        Entity AddChild(Entity entity) {
            entity.GetComponent<RelationshipComponent>().ParentHandle = GetComponent<IDComponent>().ID;
            GetComponent<RelationshipComponent>().Children.emplace_back(entity.GetComponent<IDComponent>().ID);
            return *this;
        }

        bool HasChildren() {
            if (HasAny<RelationshipComponent>())
                return GetComponent<RelationshipComponent>().Children.size() > 0;
            return false;
        }

        auto GetChildren() {
            if (HasAny<RelationshipComponent>())
                return GetComponent<RelationshipComponent>().Children;
            return std::vector<UUID>{};
        }

        auto GetUUID() {
            if (HasComponent<IDComponent>())
                return GetComponent<IDComponent>().ID;
            return UUID(0);
        }

        operator uint32_t() { return (uint32_t) m_EntityHandle; }

        operator entt::entity() { return m_EntityHandle; }

        operator const entt::entity() const { return m_EntityHandle; }

        operator bool() { return (m_EntityHandle != entt::null) && m_Scene; }

        bool operator==(const Entity &other) const {
            return (m_EntityHandle == other.m_EntityHandle) && m_Scene == other.m_Scene;
        }

        bool operator!=(const Entity &other) const {
            return !(*this == other);
        }

        bool IsValid() { return m_EntityHandle != entt::null && m_Scene != nullptr; }

        const bool IsValid() const { return m_EntityHandle != entt::null && m_Scene != nullptr; }

        entt::entity m_EntityHandle = {};
        Scene *m_Scene{};

        friend class Scene;
    };
}