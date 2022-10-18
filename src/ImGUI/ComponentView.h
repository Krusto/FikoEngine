#pragma once
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>

namespace FikoEngine {
    class ComponentView {
    public:
        static void ShowProperties(Entity entity, TagComponent &component);

        static void ShowProperties(Entity entity, TransformComponent &component);

        static void ShowProperties(Entity entity, MaterialComponent &component);

        static void ShowProperties(Entity entity, DrawableComponent &component);

        static void ShowProperties(Entity entity, CameraComponent &component);

        static void ShowProperties(Entity entity, MeshComponent &component);

        static bool DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f,
                                    float columnWidth = 100.0f);

        static bool DrawVec4Control(const std::string &label, glm::vec4 &values, float resetValue = 0.0f,
                                    float columnWidth = 100.0f);
    };
}