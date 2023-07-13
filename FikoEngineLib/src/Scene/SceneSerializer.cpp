//
// Created by Krusto on 18-Jun-23.
//

#include "SceneSerializer.hpp"
#include <fstream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

/*
IDComponent
TagComponent
TransformComponent
RelationshipComponent
MeshComponent
MaterialComponent
TextureComponent
CameraComponent
*/

namespace YAML {
    Emitter& operator<<(YAML::Emitter& out,const glm::vec3& v){
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }
    Emitter& operator<<(YAML::Emitter& out,const glm::vec4& v){
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }
    template<>
    struct [[maybe_unused]] convert<glm::vec2> {
        [[maybe_unused]] static Node encode(const glm::vec2& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, glm::vec2& rhs) {
            if(!node.IsSequence() || node.size() != 2) {
                return false;
            }
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<glm::vec3> {
        [[maybe_unused]] static Node encode(const glm::vec3& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, glm::vec3& rhs) {
            if(!node.IsSequence() || node.size() != 3) {
                return false;
            }
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<glm::vec4> {
        [[maybe_unused]] static Node encode(const glm::vec4& rhs) {
            Node node;
            node.push_back(rhs.w);
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, glm::vec4& rhs) {
            if(!node.IsSequence() || node.size() != 4) {
                return false;
            }
            rhs.w = node[0].as<float>();
            rhs.x = node[1].as<float>();
            rhs.y = node[2].as<float>();
            rhs.z = node[3].as<float>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::IDComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::IDComponent& rhs) {
            Node node(YAML::NodeType::Map);
            node["IDComponent"]["UUID"] = (uint64_t)rhs.ID;
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::IDComponent& rhs) {
            rhs.ID = node["UUID"].as<uint64_t>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::TagComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::TagComponent& rhs) {
            Node node;
            node["TagComponent"].push_back(std::pair("Tag",rhs.Tag));
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::TagComponent& rhs) {
            rhs.Tag = node["Tag"].as<std::string>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::TransformComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::TransformComponent& rhs) {
            Node node;
            node["TransformComponent"].push_back("Position");
            node["TransformComponent"].push_back("Rotation");
            node["TransformComponent"].push_back("Scale");
            node["TransformComponent"]["Position"].push_back(rhs.position);
            node["TransformComponent"]["Rotation"].push_back(rhs.rotation);
            node["TransformComponent"]["Size"].push_back(rhs.size);
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::TransformComponent& rhs) {
            rhs.position = node["Position"].as<glm::vec3>();
            rhs.rotation = node["Rotation"].as<glm::vec3>();
            rhs.size = node["Scale"].as<glm::vec3>();

            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::RelationshipComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::RelationshipComponent& rhs) {
            Node node;
            node["RelationshipComponent"].push_back("ParentHandle");
            node["RelationshipComponent"].push_back("Children");
            node["RelationshipComponent"]["ParentHandle"].push_back(rhs.ParentHandle.GetID());
            for(auto& child : rhs.Children)
               node["RelationshipComponent"]["Children"].push_back(child.GetID());
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::RelationshipComponent& rhs) {
            rhs.ParentHandle = node["ParentHandle"].as<uint64_t>();
            if(node["Children"].size() < 1)
                return true;

            for (auto it = node["Children"].begin(); it != node["Children"].end(); ++it) {
                rhs.Children.emplace_back(it->as<uint64_t>());
            }
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::MeshComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::MeshComponent& rhs) {
            Node node;
            node["MeshComponent"].push_back(std::pair("Mesh Type",(int)rhs.type));
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::MeshComponent& rhs) {
            rhs.type = (FikoEngine::MeshType)node["Mesh Type"].as<uint32_t>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::MaterialComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::MaterialComponent& rhs) {
            using namespace FikoEngine;
            Node node;

            if(rhs.material.IsValid()) {
                auto material = rhs.material.Lock();
                if (material->GetShader().IsValid()) {
                    auto shader = material->GetShader().Lock();
                    node["MaterialComponent"].push_back(std::pair("Is Light Dependent",rhs.isLightDependent));
                    node["MaterialComponent"].push_back("Material");
                    node["MaterialComponent"]["Material"].push_back(std::pair("Material Name",material->GetName().data()));
                    node["MaterialComponent"]["Material"];

                    auto &buffer = (*shader->GetShaderBuffers().begin()).second;
                    const auto &uniforms = buffer.Uniforms;
                    for (const auto &uniform: uniforms) {
                        auto type = uniform.second.m_Type;
                        if (type == ShaderUniformType::Float) {
                            auto &value = material->GetFloat(uniform.first);
                            node["MaterialComponent"]["Material"].push_back(std::pair(uniform.first,value));
                        }
                        if (type == ShaderUniformType::Vec3) {
                            auto &value = material->GetVector3(uniform.first);
                            node["MaterialComponent"]["Material"].push_back(std::pair(uniform.first,value));
                        }
                        if (type == ShaderUniformType::Vec4) {
                            auto &value = material->GetVector4(uniform.first);
                            node["MaterialComponent"]["Material"].push_back(std::pair(uniform.first,value));
                        }
                    }
                }
            }

            return node;
        }
        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::MaterialComponent& rhs) {
            rhs.isLightDependent = node["Is Light Dependent"].as<bool>();
            rhs.name = node["Material"].as<std::string>();
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::CameraComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::CameraComponent& rhs) {
            Node node;
            node["CameraComponent"].push_back(std::pair("Primary",rhs.primary));
            node["CameraComponent"].push_back("Position");
            node["CameraComponent"].push_back("Rotation");
            node["CameraComponent"]["Position"].push_back(rhs.camera->GetPosition());
            node["CameraComponent"]["Rotation"].push_back(rhs.camera->GetRotation());
            node["CameraComponent"].push_back("Specification");
            node["CameraComponent"]["Specification"].push_back(std::pair("FOV",rhs.camera->GetSpec().fov));
            node["CameraComponent"]["Specification"].push_back(std::pair("Far",rhs.camera->GetSpec().Far));
            node["CameraComponent"]["Specification"].push_back(std::pair("Near",rhs.camera->GetSpec().Near));
            node["CameraComponent"]["Specification"].push_back(std::pair("Viewport Width",rhs.camera->GetSpec().viewport.width));
            node["CameraComponent"]["Specification"].push_back(std::pair("Viewport Height",rhs.camera->GetSpec().viewport.height));
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::CameraComponent& rhs) {
            using namespace FikoEngine;

            rhs.primary = node["Primary"].as<bool>();

            CameraSpec spec;
            spec.fov = node["Specification"]["FOV"].as<float>();
            spec.Far = node["Specification"]["Far"].as<float>();
            spec.Near = node["Specification"]["Near"].as<float>();
            spec.viewport.width = node["Specification"]["Viewport Width"].as<uint32_t>();
            spec.viewport.height = node["Specification"]["Viewport Height"].as<uint32_t>();

            rhs.camera = Ref<Camera>::Create(spec);
            rhs.camera->SetPosition(node["Position"].as<glm::vec3>());
            rhs.camera->SetRotation(node["Rotation"].as<glm::vec3>());
            return true;
        }
    };
    template<>
    struct [[maybe_unused]] convert<FikoEngine::LightComponent> {
        [[maybe_unused]] static Node encode(const FikoEngine::LightComponent& rhs) {
            Node node;
            node["LightComponent"].push_back("Position");
            node["LightComponent"].push_back("Ambient Color");
            node["LightComponent"].push_back("Diffuse Color");
            node["LightComponent"].push_back("Specular Color");
            node["LightComponent"]["Position"].push_back(rhs.position);
            node["LightComponent"]["Ambient Color"].push_back(rhs.ambientColor);
            node["LightComponent"]["Diffuse Color"].push_back(rhs.diffuseColor);
            node["LightComponent"]["Specular Color"].push_back(rhs.specularColor);
            node["LightComponent"]["Intensity"].push_back(rhs.intensity);
            return node;
        }

        [[maybe_unused]] static bool decode(const Node& node, FikoEngine::LightComponent& rhs) {
            rhs.position = node["Position"].as<glm::vec3>();
            rhs.ambientColor = node["Ambient Color"].as<glm::vec3>();
            rhs.diffuseColor = node["Diffuse Color"].as<glm::vec3>();
            rhs.specularColor = node["Specular Color"].as<glm::vec3>();
            rhs.intensity = node["Intensity"].as<float>();

            return true;
        }
    };
}

namespace FikoEngine {

    void SceneSerializer::Serialize(std::string_view path, Scene *scene) {
        YAML::Emitter out;

        out << YAML::BeginMap;
            out << YAML::Key << "Scene" << YAML::Value << scene->GetHandle().GetComponent<TagComponent>().Tag;
            out << YAML::Key << "SceneID" << YAML::Value << (uint64_t)scene->GetID();
            out << YAML::Key << "Entity count" << YAML::Value << scene->m_EntityMap.size();
            out << YAML::Key << "Shader count" << YAML::Value << scene->m_ShaderLibrary.size();
            out << YAML::Key << "Material count" << YAML::Value << scene->m_MaterialLibrary.size();

            out << YAML::Key << "Shaders" << YAML::Value;
            out << YAML::BeginSeq;
            for(auto& [name,shader] : scene->m_ShaderLibrary){
                SerializeShader(&out,scene,shader);
            }
            out << YAML::EndSeq;

            out << YAML::Key << "Materials" << YAML::Value;
            out << YAML::BeginSeq;
            for(auto& [name,material] : scene->m_MaterialLibrary){
                SerializeMaterial(&out,scene,material);
            }
            out << YAML::EndSeq;

            out << YAML::Key << "Entities" << YAML::Value;
            out << YAML::BeginSeq;
            for(auto& [uid,entity] : scene->m_EntityMap){
                if(entity.IsValid())
                    SerializeEntity(&out,scene,entity);
            }
            out << YAML::EndSeq;

        out << YAML::EndMap;

        std::ofstream fout;
        fout.open(std::string(path),std::ios::trunc);
        if(fout.good() && fout.is_open()) {
            fout << out.c_str();
            fout.close();
        }

    }
    Scene *SceneSerializer::Deserialize(std::string_view path) {
        Scene *scene = nullptr;
        try {
            std::string SceneLocation = std::filesystem::path(path).parent_path().string();
            std::string FileName = std::filesystem::path(path).filename().string();

            LOG_INFO("Loading " + FileName + " scene file!");

            YAML::Node config = YAML::LoadFile(path.data());
            if (config.size() < 8) // ensure all necessary keys are available
                return nullptr;

            auto SceneID = config["SceneID"].as<uint64_t>();
            auto SceneName = config["Scene"].as<std::string>();
            scene = new Scene(SceneName, SceneLocation);
            scene->m_SceneID = SceneID;

            auto entityCount = config["Entity count"].as<uint32_t>();
            LOG_INFO("Entity count : " + std::to_string(entityCount));
            YAML::Node entities = config["Entities"];
            LOG_INFO("Entity count found : " + std::to_string(entities.size()));

            auto shaderCount = config["Shader count"].as<uint32_t>();
            LOG_INFO("Shader count : " + std::to_string(shaderCount));
            YAML::Node shaders = config["Shaders"];
            LOG_INFO("Shader count found : " + std::to_string(entities.size()));

            auto materialCount = config["Material count"].as<uint32_t>();
            LOG_INFO("Material count : " + std::to_string(materialCount));
            YAML::Node materials = config["Materials"];
            LOG_INFO("Material count found : " + std::to_string(materials.size()));

            DeserializeShaders(shaders, scene);
            DeserializeMaterials(materials, scene);
            DeserializeEntities(entities, scene);
        }catch(const std::exception& e){
            LOG_ERROR(e.what());
        }
        return scene;
    }

    void SceneSerializer::DeserializeEntity(YAML::Node node,Scene* scene){
        switch (node["Entity"].Type()) {
            case YAML::NodeType::Map: {
                Entity entity = scene->CreateEmptyEntity();
                LOG_INFO("Entity component count : " + std::to_string(node["Entity"].size()));
                for (auto it = node["Entity"].begin(); it != node["Entity"].end(); ++it) {
                    auto key = it->first.as<std::string>();
                    LOG_INFO("-" + key);
                }
                for (auto it = node["Entity"].begin(); it != node["Entity"].end(); ++it) {
                    auto key = it->first.as<std::string>();
                    DeserializeComponent(entity,key, it->second);
                }

                break;
            }
            default:
                break;
        }
    }
    void SceneSerializer::DeserializeMaterials(YAML::Node node,Scene* scene) {
        switch (node.Type()) {
            case YAML::NodeType::Sequence:
                for (auto it = node.begin(); it != node.end(); ++it) {
                    DeserializeMaterial(*it,scene);
                }
            default:
                break;
        }
    }
    void SceneSerializer::DeserializeMaterial(YAML::Node node,Scene* scene){
        switch (node.Type()) {
            case YAML::NodeType::Map: {
                for (auto it = node["Material"].begin(); it != node["Material"].end(); ++it) {
                    if(!it->second.IsSequence() && !it->second.IsMap())
                    LOG_INFO(it->first.as<std::string>() + " : " + it->second.as<std::string>());
                }

                auto materialName = node["Material"]["Material Name"].as<std::string>();
                auto shaderName = node["Material"]["Shader"].as<std::string>();
                scene->AddMaterial(materialName,shaderName);
                auto material = scene->GetMaterial(materialName).Lock();
                if(node["Material"]["Uniforms"].size() > 1 && material) {
                    LOG_INFO("Uniforms:");
                    auto shader = scene->GetShader(shaderName).Lock();
                    for (auto it = node["Material"]["Uniforms"].begin();
                    it != node["Material"]["Uniforms"].end(); ++it) {
                        auto uniformName = it->first.as<std::string>();
                        auto uniformNode = node["Material"]["Uniforms"][uniformName];
                        if(uniformNode.IsSequence()){
                            switch(uniformNode.size()){
                                case 2:
                                    material->Set(uniformName,uniformNode.as<glm::vec2>());
                                    LOG_INFO(uniformName + " : " + glm::to_string(material->GetVector2(uniformName)));
                                    break;
                                case 3:
                                    material->Set(uniformName,uniformNode.as<glm::vec3>());
                                    LOG_INFO(uniformName + " : " + glm::to_string(material->GetVector3(uniformName)));
                                    break;
                                case 4:
                                    material->Set(uniformName,uniformNode.as<glm::vec4>());
                                    LOG_INFO(uniformName + " : " + glm::to_string(material->GetVector4(uniformName)));
                                    break;
                            }
                        }else if(uniformNode.IsScalar()){
                            material->Set(uniformName,uniformNode.as<float>());
                            LOG_INFO(uniformName + " : " + std::to_string(material->GetFloat(uniformName)));
                        }

                    }
                }
                break;
            }
            default:
                break;
        }
    }
    void SceneSerializer::DeserializeShaders(YAML::Node node,Scene* scene){
        switch (node.Type()) {
            case YAML::NodeType::Sequence:
                for (auto it = node.begin(); it != node.end(); ++it) {
                    DeserializeShader(*it,scene);
                }
            default:
                break;
        }
    }
    void SceneSerializer::DeserializeShader(YAML::Node node,Scene* scene) {
        switch (node.Type()) {
            case YAML::NodeType::Map: {
                for (auto it = node["Shader"].begin(); it != node["Shader"].end(); ++it) {
                    if(!it->second.IsSequence() && !it->second.IsMap())
                        LOG_INFO(it->first.as<std::string>() + " : " + it->second.as<std::string>());
                }

                auto shaderName = node["Shader"]["Name"].as<std::string>();
                auto relativeShaderPath = node["Shader"]["Path"].as<std::string>();
                if(node["Shader"]["Resources"].size())
                    LOG_INFO("Resources:");

                auto scenePath = scene->GetHandle().GetComponent<FileComponent>().Path;
                auto shaderPath = std::filesystem::path(scenePath).append(relativeShaderPath).append(shaderName).string();
                scene->AddShader(shaderName,shaderPath);
                auto shader = scene->GetShader(shaderName).Lock();
                for (auto it = node["Shader"]["Resources"].begin(); it != node["Shader"]["Resources"].end(); ++it) {
                    auto resourceName = it->first.as<std::string>();
                    auto resourceRegister = it->second.as<uint32_t>();
                    LOG_INFO(resourceName + " : " + std::to_string(resourceRegister));
                    if(shader)
                        shader->AddResource(it->first.as<std::string>(),ShaderResourceDeclaration(resourceName,resourceRegister,1));
                }
                break;
            }
            default:
                break;
        }
    }
    void SceneSerializer::DeserializeEntities(YAML::Node node,Scene* scene){
        switch (node.Type()) {
            case YAML::NodeType::Sequence:
                for (auto it = node.begin(); it != node.end(); ++it)
                    DeserializeEntity(*it,scene);
                break;
            default:
                break;
        }
    }
    void SceneSerializer::SerializeEntity(YAML::Emitter* out,Scene* scene,Entity entity){
        *out << YAML::BeginMap;
        *out << YAML::Key << "Entity" << YAML::Value;
        *out << YAML::BeginMap;
        if(entity.HasComponent<IDComponent>()){
            SerializeComponent(out,entity.GetComponent<IDComponent>());
        }
        if(entity.HasComponent<TagComponent>()){
            SerializeComponent(out,entity.GetComponent<TagComponent>());
        }
        if(entity.HasComponent<TransformComponent>()){
            SerializeComponent(out,entity.GetComponent<TransformComponent>());
        }
        if(entity.HasComponent<CameraComponent>()){
            SerializeComponent(out,entity.GetComponent<CameraComponent>());
        }
        if(entity.HasComponent<MaterialComponent>()){
            SerializeComponent(out,entity.GetComponent<MaterialComponent>());
        }
        if(entity.HasComponent<MeshComponent>()){
            SerializeComponent(out,entity.GetComponent<MeshComponent>());
        }
        if(entity.HasComponent<RelationshipComponent>()){
            SerializeComponent(out,entity.GetComponent<RelationshipComponent>());
        }
        if(entity.HasComponent<TextureComponent>()){
            SerializeComponent(out,entity.GetComponent<TextureComponent>());
        }
        if(entity.HasComponent<LightComponent>()){
            SerializeComponent(out,entity.GetComponent<LightComponent>());
        }
        *out << YAML::EndMap;
        *out << YAML::EndMap;

    }
    void SceneSerializer::SerializeShader(YAML::Emitter *out,Scene* scene,Shader* shader) {

        *out << YAML::BeginMap;
        *out << YAML::Key << "Shader" << YAML::Value;
            *out << YAML::BeginMap;
                *out << YAML::Key << "Name" << YAML::Value << shader->GetName();
                *out << YAML::Key << "Path" << YAML::Value << std::filesystem::relative(shader->GetPath(),scene->GetHandle().GetComponent<FileComponent>().Path).string();

                *out << YAML::Key << "Resources" << YAML::Value;
                *out << YAML::BeginMap;
                    for(auto& [name,resource] : shader->GetResources()){
                        *out << YAML::Key << name << YAML::Value << resource.GetRegister();
                    }
                *out << YAML::EndMap;
            *out << YAML::EndMap;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeMaterial(YAML::Emitter* out,Scene* scene,Material* material){
        if(material != nullptr) {
            if (material->GetShader().IsValid()) {
                auto shader = material->GetShader().Lock();
                *out << YAML::BeginMap;
                *out << YAML::Key << "Material" << YAML::Value;
                    *out << YAML::BeginMap;
                        *out << YAML::Key << "Material Name" << YAML::Value << std::string(material->GetName());
                        *out << YAML::Key << "Shader" << YAML::Value << shader->GetName();
                        *out << YAML::Key << "Uniforms" << YAML::Value;
                        *out << YAML::BeginMap;
                            auto &buffer = (*shader->GetShaderBuffers().begin()).second;
                            const auto &uniforms = buffer.Uniforms;
                            for (const auto &uniform: uniforms) {
                                auto type = uniform.second.m_Type;
                                if (type == ShaderUniformType::Float) {
                                    auto &value = material->GetFloat(uniform.first);
                                    *out << YAML::Key << uniform.first << YAML::Value << value;
                                }
                                if (type == ShaderUniformType::Vec3) {
                                    auto &value = material->GetVector3(uniform.first);
                                    *out << YAML::Key << uniform.first << YAML::Value << value;
                                }
                                if (type == ShaderUniformType::Vec4) {
                                    auto &value = material->GetVector4(uniform.first);
                                    *out << YAML::Key << uniform.first << YAML::Value << value;
                                }
                            }
                        *out << YAML::EndMap;
                    *out << YAML::EndMap;
                *out << YAML::EndMap;
            }
        }
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter *out, const IDComponent &component) {
        *out << YAML::Key << "IDComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "UUID" << YAML::Value << component.ID;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter *out, const TagComponent &component) {
        *out << YAML::Key << "TagComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "Tag" << YAML::Value << component.Tag;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter *out, const TransformComponent &component) {
        *out << YAML::Key << "TransformComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "Position" << YAML::Value << component.position;
        *out << YAML::Key << "Rotation" << YAML::Value << component.rotation;
        *out << YAML::Key << "Scale" << YAML::Value << component.size;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter *out, const RelationshipComponent &component) {
        *out << YAML::Key << "RelationshipComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "ParentHandle" << YAML::Value << component.ParentHandle;
        *out << YAML::Key << "Children" << YAML::Value;
        *out << YAML::BeginSeq;
        for(auto& child : component.Children)
            *out << child;
        *out << YAML::EndSeq;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter* out, const MeshComponent& component){
        *out << YAML::Key << "MeshComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "Mesh Type" << YAML::Value << (int)component.type;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter* out, const MaterialComponent& component){
        if(component.material.IsValid()) {
            auto material = component.material.Lock();
            if (material->GetShader().IsValid()) {
                auto shader = material->GetShader().Lock();
                *out << YAML::Key << "MaterialComponent";
                *out << YAML::BeginMap;
                *out << YAML::Key << "Is Light Dependent" << YAML::Value << component.isLightDependent;
                *out << YAML::Key << "Material" << YAML::Value << std::string(material->GetName());
                *out << YAML::EndMap;
            }
        }
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter* out, const TextureComponent& component){
        *out << YAML::Key << "TextureComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "Name" << YAML::Value << component.name;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter* out, const CameraComponent& component){
        *out << YAML::Key << "CameraComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "Primary" << YAML::Value << component.primary;
        *out << YAML::Key << "Position" << YAML::Value << component.camera->GetPosition();
        *out << YAML::Key << "Rotation" << YAML::Value << component.camera->GetRotation();
        *out << YAML::Key << "Specification" << YAML::Value;
        *out << YAML::BeginMap;
        *out << YAML::Key << "FOV" << YAML::Value << component.camera->GetSpec().fov;
        *out << YAML::Key << "Far" << YAML::Value << component.camera->GetSpec().Far;
        *out << YAML::Key << "Near" << YAML::Value << component.camera->GetSpec().Near;
        *out << YAML::Key << "Viewport Width" << YAML::Value << component.camera->GetSpec().viewport.width;
        *out << YAML::Key << "Viewport Height" << YAML::Value << component.camera->GetSpec().viewport.height;
        *out << YAML::EndMap;
        *out << YAML::EndMap;
    }
    void SceneSerializer::SerializeComponent(YAML::Emitter* out, const LightComponent& component){
        *out << YAML::Key << "LightComponent";
        *out << YAML::BeginMap;
        *out << YAML::Key << "Position" << YAML::Value << component.position;
        *out << YAML::Key << "Ambient Color" << YAML::Value << component.ambientColor;
        *out << YAML::Key << "Diffuse Color" << YAML::Value << component.diffuseColor;
        *out << YAML::Key << "Specular Color" << YAML::Value << component.specularColor;
        *out << YAML::Key << "Intensity" << YAML::Value << component.intensity;
        *out << YAML::EndMap;
    }

    void SceneSerializer::DeserializeComponent(Entity entity,const std::string& key,YAML::Node& node){
        if(key == "IDComponent"){
            entity.AddComponent<IDComponent>();
            entity.GetComponent<IDComponent>() = node.as<IDComponent>();
            LOG_INFO("    -IDComponent");
        }else if(key == "TagComponent"){
            entity.AddComponent<TagComponent>();
            entity.GetComponent<TagComponent>() = node.as<TagComponent>();
            LOG_INFO("    -TagComponent");
        }else if(key == "TransformComponent"){
            entity.AddComponent<TransformComponent>();
            entity.GetComponent<TransformComponent>() = node.as<TransformComponent>();
            LOG_INFO("    -TransformComponent");
        }else if(key == "RelationshipComponent"){
            entity.AddComponent<RelationshipComponent>();
            entity.GetComponent<RelationshipComponent>() = node.as<RelationshipComponent>();
            if(entity.IsValid() &&
            entity.GetComponent<RelationshipComponent>().ParentHandle == entity.GetScene()->GetID())
                entity.GetScene()->AddEntity(entity);
            LOG_INFO("    -RelationshipComponent");
        }else if(key == "MeshComponent"){
            entity.AddComponent<MeshComponent>();
            entity.GetComponent<MeshComponent>() = node.as<MeshComponent>();
            auto type = entity.GetComponent<MeshComponent>().type;
            if(type != MeshType::Custom && type != MeshType::None){
                entity.GetComponent<MeshComponent>() = MeshComponent::Generate(type);
            }
            LOG_INFO("    -MeshComponent");
        }else if(key == "MaterialComponent"){
            entity.AddComponent<MaterialComponent>();
            entity.GetComponent<MaterialComponent>() = node.as<MaterialComponent>();
            entity.GetComponent<MaterialComponent>().material = entity.m_Scene->GetMaterial(entity.GetComponent<MaterialComponent>().name);
            LOG_INFO("    -MaterialComponent");
        }else if(key == "CameraComponent"){
            entity.AddComponent<CameraComponent>();
            entity.GetComponent<CameraComponent>() = node.as<CameraComponent>();
            LOG_INFO("    -CameraComponent");
        }if(key == "LightComponent"){
            entity.AddComponent<LightComponent>();
            entity.GetComponent<LightComponent>() = node.as<LightComponent>();
            LOG_INFO("    -LightComponent");
        }
    }

}
