#pragma once
#include <entt/entt.hpp>
#include <Core/Ref.h>
#include <Scene/Component.h>
#include <Scene/Scene.h>
namespace FikoEngine {
    class Entity {
    public:
        Entity() = default;
        ~Entity() = default;

        Entity(uint32_t entityHandle, Scene* scene) :
                m_EntityHandle((entt::entity) entityHandle), m_Scene(scene) {}

        Entity(entt::entity entityHandle, Scene* scene) :
                m_EntityHandle(entityHandle), m_Scene(scene) {}

        Entity(const Entity& entity) = default;

        template<typename T>
        T& GetComponent() {
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        [[nodiscard]] [[nodiscard]] T& GetComponent() const {
            return &m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() {
            if (m_Scene != nullptr)
                return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
            return false;
        }

        template<typename T>
        [[maybe_unused]] [[nodiscard]] bool HasComponent() const {
            if (m_Scene != nullptr)
                return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
            return false;
        }

        template<typename T>
        void RemoveComponent() {
            if (m_Scene != nullptr)
                m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        template<typename...T>
        [[maybe_unused]]bool HasAny() {
            if (m_Scene != nullptr)
                return m_Scene->m_Registry.any_of<T...>(m_EntityHandle);
            return false;
        }

        template<typename...T>
        [[maybe_unused]] [[nodiscard]] bool HasAny() const {
            if (m_Scene != nullptr)
                return m_Scene->m_Registry.any_of<T...>(m_EntityHandle);
            return false;
        }

        template<typename T>
        Entity AddComponent() {
            if (m_Scene != nullptr)
                m_Scene->m_Registry.emplace<T>(m_EntityHandle);
            return *this;

        }

        template <typename T>
        Entity AddComponents(){
            return AddComponent<T>();
        }


        template<typename T,typename T2,typename ...others,const size_t size=sizeof...(others)>
        Entity AddComponents() {
            AddComponent<T>();
            AddComponents<T2,others...>();

            return *this;
        }

        [[nodiscard]] bool HasParents() const {
            return m_Scene->m_Registry.get<RelationshipComponent>(m_EntityHandle).ParentHandle != 0;
        }

        [[maybe_unused]] Entity AddChild(Entity entity) {
            entity.GetComponent<RelationshipComponent>().ParentHandle = this->GetComponent<IDComponent>().ID;
            entity.GetComponent<RelationshipComponent>().AddChild(entity.GetComponent<IDComponent>().ID);
            return *this;
        }

        bool HasChildren() {
            return !GetComponent<RelationshipComponent>().Children.empty();
        }

        auto GetChildren() {
            return GetComponent<RelationshipComponent>().Children;
        }

        UUID GetUUID() {
            if (HasComponent<IDComponent>())
                return GetComponent<IDComponent>().ID;
            return {0};
        }

        explicit operator uint32_t() const { return (uint32_t) m_EntityHandle; }

        explicit operator entt::entity() const { return m_EntityHandle; }

        explicit operator bool() const { return (m_EntityHandle != entt::null) && m_Scene; }

        Entity& operator=(const Entity& other) = default;

        bool operator==(const Entity &other) const {
            return (m_EntityHandle == other.m_EntityHandle) && m_Scene == other.m_Scene;
        }

        bool operator!=(const Entity &other) const {
            return !(*this == other);
        }

        [[nodiscard]] bool IsValid() const { return m_EntityHandle != entt::null && m_Scene != nullptr; }

        [[nodiscard]] Scene* GetScene() const { return m_Scene;}

        entt::entity m_EntityHandle = {entt::null};
        Scene* m_Scene{};

        friend class Scene;
    };
}