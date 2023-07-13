#pragma once
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>
namespace FikoEngine {
    class ComponentView {
    public:
        static void ShowProperties(Entity entity, TagComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, TransformComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, MaterialComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, DrawableComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, CameraComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, MeshComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, LightComponent &component, WeakRef<Window> window);

        static void ShowProperties(Entity entity, TextureComponent &component, WeakRef<Window> window);

        static bool DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f,
                                    float columnWidth = 100.0f);

        static bool DrawVec4Control(const std::string &label, glm::vec4 &values, float resetValue = 0.0f,
                                    float columnWidth = 100.0f);

        static int LoadAndDrawTexture(Entity entity, WeakRef<Material> material, const std::string &label, std::string_view textureType,WeakRef<Window> window);
    };
}