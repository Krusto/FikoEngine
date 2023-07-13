#pragma once
#include <Core/UUID.h>
#include <Core/Ref.h>
#include <Renderer/Mesh.h>
#include <Renderer/Renderer.h>
#include "Renderer/Camera.h"
#include "Renderer/Material.h"
#include "Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FikoEngine{
    class Entity;

    struct IDComponent
    {
        UUID ID = 0;
    };
    struct TagComponent
    {
    public:
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent &other) = default;
        explicit TagComponent(std::string_view tag) : Tag(tag) {}

        explicit operator std::string &() { return Tag; }
        explicit operator const std::string &() const { return Tag; }
        UUID id() { return m_id; }
    private:
        UUID m_id;
    };
    struct FileComponent
    {
    public:
        std::string Path;

        FileComponent() =
        default;
        FileComponent(
                const FileComponent &other) = default;
        explicit FileComponent(std::string_view path)
        : Path(path){}

        explicit operator std::string &() { return Path; }
        explicit operator const std::string &() const { return Path; }
        UUID id() { return m_id; }
    private:
        UUID m_id;
    };
    struct RelationshipComponent
    {
    public:
        UUID ParentHandle = 0;
        std::vector<UUID> Children;

        RelationshipComponent() = default;
        RelationshipComponent(const RelationshipComponent &other) = default;
        explicit RelationshipComponent(const UUID& parent)
           : ParentHandle(parent){}
        ~RelationshipComponent() = default;
        void AddChild(const UUID& id){Children.push_back(id);}
    };
    struct MeshComponent
    {
    public:
        Mesh mesh;
        MeshType type = MeshType::Custom;

        static MeshComponent Generate(MeshType type);

        auto &GetVA() { return va; }
        const auto &GetVA() const { return va; }

        MeshComponent() = default;
        MeshComponent(const MeshComponent &other) = default;
        explicit MeshComponent(Mesh &mesh): mesh(std::move(mesh)) {}
        UUID id() { return m_id; }
    private:
        Ref<VertexArray> va{};
        UUID m_id;
    };
    struct MaterialComponent {
    public:
        MaterialComponent() =
        default;
        MaterialComponent(
                const MaterialComponent &other) = default;
        MaterialComponent(std::string_view name,WeakRef<Material> material,bool isLightDependent = false)
            : material(material),isLightDependent(isLightDependent),name(name){}

        WeakRef<Material> material{};
        bool isLightDependent{};
        std::string name{};

        UUID id() { return m_id; }
    private:
        UUID m_id;
    };
    struct TextureComponent {
    public:
        std::string name;
        TextureComponent() = default;
        TextureComponent(const TextureComponent& other) = default;
        explicit TextureComponent(std::string_view name) :
                name(name) {}
        UUID id() { return m_id; }
    private:
        UUID m_id;
    };
    struct LightComponent {
    public:
        glm::vec3 position{};
        glm::vec3 ambientColor{};
        glm::vec3 diffuseColor{};
        glm::vec3 specularColor{};
        float intensity{};
        LightComponent() = default;
        LightComponent(const LightComponent& other) = default;
        UUID id() { return m_id; }
    private:
        UUID m_id;
    };
    struct TransformComponent {
    public:
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 size{1.0f, 1.0f, 1.0f};
        TransformComponent() =
        default;
        TransformComponent(
                const TransformComponent &other) = default;
        TransformComponent(glm::vec3
                           position, glm::vec3
                           rotation, glm::vec3
                           size) :
                position(position), rotation(rotation), size(size)
        {}
        uint64_t id() { return m_id; }

        [[nodiscard]] glm::mat4 GetTransform() const {
            return
                    glm::translate(glm::mat4(1.0f), position) *
                    glm::rotate(glm::mat4(1.0f), rotation.x, {1, 0, 0}) *
                    glm::rotate(glm::mat4(1.0f), rotation.y, {0, 1, 0}) *
                    glm::rotate(glm::mat4(1.0f), rotation.z, {0, 0, 1}) *
                    glm::scale(glm::mat4(1.0f), size);
        }
    private:
        UUID m_id;
    };
    struct CameraComponent {
        Ref<Camera> camera;
        bool primary = false;
        CameraComponent() =
        default;
        CameraComponent(
                const CameraComponent &other) = default;

    };
    struct DrawableComponent
    {
    public:
        DrawableComponent() =
        default;
        DrawableComponent(
                const DrawableComponent &other) = default;

        [[maybe_unused]] static DrawableComponent Generate(Entity entity);

        ~DrawableComponent();
        
        auto &GetVA() { return va; }
        const auto &GetVA() const { return va; }
        UUID id() { return m_id; }
    private:
        UUID m_id;
        Ref<VertexArray> va;
    };
}