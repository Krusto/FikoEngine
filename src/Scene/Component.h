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

            TagComponent() =
            default;
            TagComponent(
            const TagComponent &other) = default;
            TagComponent(
            const std::string &tag)
            : Tag(tag)
            {}

            operator std::string &()
            { return Tag; }
            operator const std::string &() const { return Tag; }
            UUID id() { return m_id; }
            private:
            UUID m_id;
        };
        struct RelationshipComponent
        {
            public:
            UUID ParentHandle = 0;
            std::vector<UUID> Children;

            RelationshipComponent() =
            default;
            RelationshipComponent(
            const RelationshipComponent &other) = default;
            RelationshipComponent(UUID
            parent)
            : ParentHandle(parent)
            {}
        };
        struct MeshComponent
        {
            public:
            Mesh mesh;
            MeshType type = MeshType::Custom;

            static MeshComponent Generate(Entity entity, MeshType type);

            auto &GetVA() { return va; }
            const auto &GetVA() const { return va; }

            MeshComponent() =
            default;
            MeshComponent(
            const MeshComponent &other) = default;
            MeshComponent(
            const Mesh &mesh):
            mesh(mesh)
            {}
            UUID id() { return m_id; }
            private:
            Ref<VertexArray> va;
            UUID m_id;
        };

        struct MaterialComponent {
            public:
            Ref<Material> material;
            MaterialComponent() =
            default;
            MaterialComponent(
            const MaterialComponent &other) = default;
            MaterialComponent(Ref<Material>
            material) :
            material(material)
            {}
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

            glm::mat4 GetTransform() {
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

            static DrawableComponent Generate(Entity entity);

            auto &GetVA() { return va; }
            const auto &GetVA() const { return va; }
            UUID id() { return m_id; }
            private:
            UUID m_id;
            Ref<VertexArray> va;
        };
}