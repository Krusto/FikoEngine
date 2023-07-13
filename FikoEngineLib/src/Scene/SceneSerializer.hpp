//
// Created by Krusto on 18-Jun-23.
//

#pragma once
#include <string_view>
#include <Scene/Scene.h>
#include <Scene/Entity.h>
#include <yaml-cpp/yaml.h>

namespace FikoEngine {
    class SceneSerializer {
    public:
        static void Serialize(std::string_view path, Scene *scene);
        static Scene* Deserialize(std::string_view path);

        static void SerializeComponent(YAML::Emitter* out,const IDComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const TagComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const TransformComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const RelationshipComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const MeshComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const MaterialComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const TextureComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const CameraComponent& component);
        static void SerializeComponent(YAML::Emitter* out,const LightComponent& component);
        static void DeserializeComponent(Entity entity,const std::string& key, YAML::Node& node);

        static void SerializeEntity(YAML::Emitter* out,Scene* scene,Entity entity);
        static void DeserializeEntity(YAML::Node node,Scene* scene);
        static void DeserializeEntities(YAML::Node node,Scene* scene);
        static void DeserializeMaterials(YAML::Node node,Scene* scene);
        static void DeserializeMaterial(YAML::Node node,Scene* scene);
        static void DeserializeShaders(YAML::Node node,Scene* scene);
        static void DeserializeShader(YAML::Node node,Scene* scene);

        static void SerializeShader(YAML::Emitter* out,Scene* scene,Shader* shader);
        static void SerializeMaterial(YAML::Emitter* out,Scene* scene,Material* material);
    };

}