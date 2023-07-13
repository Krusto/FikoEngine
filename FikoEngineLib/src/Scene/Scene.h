#pragma once
#include <vector>
#include <unordered_map>
#include <entt/entt.hpp>
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Renderer/Viewport.h>
#include <Renderer/Shader.h>
#include <Renderer/Material.h>

namespace FikoEngine {
    class Entity;

    class Scene : public RefCounted {
    public:
        explicit Scene(std::string_view name, std::string_view fileLocation = "");
        ~Scene();

        void Destroy();
        void OnUpdate(float dt);

        [[maybe_unused]] Entity AddEntity(std::string name = "Unnamed");
        [[maybe_unused]] Entity AddEntity(Entity entity);
        [[maybe_unused]] Entity CreateEntity(std::string name = "Unnamed");
        [[maybe_unused]] Entity CreateEmptyEntity();
        [[maybe_unused]] Entity RemoveEntity(const UUID& uuid);
        [[maybe_unused]] Entity RemoveEntity(Entity entity);
        auto data() { return m_Registry.data(); }
        Entity GetHandle();

        template<typename... Component>
        std::vector<Entity> GetEntitiesWith() {
            auto entities = m_Registry.view<Component...>();
            std::vector<Entity> output{};
            for (auto e: entities) {
                output.push_back({e, this});
            }
            return output;
        }

        bool HasUUID(const UUID& uuid);
        Entity GetEntity(const UUID& uuid);
        Entity FindEntity(const std::string &name);
        Entity GetSelectedEntity();
        Entity SetSelectedEntity(const Entity& entity);
        auto GetID() { return m_SceneID; }

        ViewportSize GetViewport() { return {m_ViewportWidth, m_ViewportHeight}; }

        WeakRef<Material> GetMaterial(std::string_view name);
        void AddMaterial(std::string_view materialName, std::string_view shaderName);

        WeakRef<Shader> GetShader(std::string_view name);
        void AddShader(std::string_view name, std::string_view path);

        WeakRef<Texture> GetTexture(std::string_view name);
        void AddTexture(std::string_view name, std::string_view path);
        void RemoveTexture(std::string_view name);

        [[maybe_unused]] auto& GetMaterials() { return m_MaterialLibrary; }
        [[maybe_unused]] auto& GetShaders() { return m_ShaderLibrary; }
        [[maybe_unused]] auto& GetTextures() { return m_TextureLibrary; }

    private:
        std::string m_SceneName{};

        entt::entity m_SceneEntity{};
        entt::entity m_SelectedEntity{};

        UUID m_SceneID{};

        entt::registry m_Registry{};
        uint32_t m_ViewportWidth{}, m_ViewportHeight{};

        std::unordered_map<UUID, Entity> m_EntityMap;
        std::unordered_map<std::string, Ref<Material>> m_MaterialLibrary;
        std::unordered_map<std::string, Ref<Shader>> m_ShaderLibrary;
        std::unordered_map<std::string, Ref<Texture>> m_TextureLibrary;

        friend class Entity;
        friend class SceneSerializer;
    };


}
