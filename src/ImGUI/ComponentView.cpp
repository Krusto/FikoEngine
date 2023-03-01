#include "ComponentView.h"
#include "Application/Application.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <Core/Platform/Windows/WindowsPlatformUtils.h>
#include <Application/Application.h>
#include <filesystem>

namespace FikoEngine {

    void ComponentView::ShowProperties(Entity entity, TagComponent &component) {
        auto &tag = component.Tag;
        std::string buffer = std::string(256, NULL);
        std::memcpy(&buffer[0], &tag[0], tag.size());
        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
        if (ImGui::InputText("##Tag", &buffer[0], buffer.size())) {
            tag = buffer;
        }
        ImGui::PopItemWidth();
    }

    void ComponentView::ShowProperties(Entity entity, TransformComponent &component) {
        DrawVec3Control("Translation", component.position);
        DrawVec3Control("Rotation", component.rotation);
        DrawVec3Control("Scale", component.size, 1.0f);

    }

    void ComponentView::ShowProperties(Entity entity, MaterialComponent &component) {
        ImGui::PushID(component.id());
        if (component.material) {
            ImGui::Text("Material name: %s", component.material->GetName().c_str());
            const auto &buffer = (*component.material->GetShader()->GetShaderBuffers().begin()).second;
            const auto &uniforms = buffer.Uniforms;
            for (const auto &uniform: uniforms) {
                auto type = uniform.second.m_Type;
                if (type == ShaderUniformType::Float) {
                    auto &value = component.material->GetFloat(uniform.first);
                    ImGui::DragFloat(uniform.first.c_str(), &value, 1, 0.0f, 100.0f, "%f");
                }
                if (type == ShaderUniformType::Vec3) {
                    auto &value = component.material->GetVector3(uniform.first);
                    ImGui::ColorEdit4(uniform.first.c_str(), &value.r, ImGuiColorEditFlags_NoAlpha);
                }
                if (type == ShaderUniformType::Vec4) {

                    auto &value = component.material->GetVector4(uniform.first);
                    ImGui::Text("%s", uniform.first.c_str());
                    ImGui::SameLine();
                    ImGui::ColorEdit4("", &value.r);
                }
            }

            ImGui::Checkbox("Is Light Dependent", &component.isLightDependent);

            uint32_t textureCount = 2;
            std::string textureTypes[] = {"Diffuse", "Specular", "Emissive"};

            for (uint32_t i = 0; i < textureCount; i++) {
                auto texture = component.material->TryGetTexture(textureTypes[i]);
                bool textureLoadNeeded = false;

                int state = LoadAndDrawTexture(entity, textureTypes[i] + " Texture", texture);

                switch (state) {
                    case 0:
                        break;
                    case 1:
                        component.material->Set(textureTypes[i], texture);
                        break;
                    case 2:
                        texture.Reset();
                        component.material->Set(textureTypes[i], Ref<Texture>{});
                        break;
                }
            }
            if (ImGui::Button("Reload Shader")) {
                component.material->Reset();
            }
        } else {
            ImGui::Text("%s", "No material type added");
        }
        auto &list = entity.m_Scene->GetMaterials();

        ImGui::SameLine();
        bool clicked = ImGui::Button("Change material");
        if (ImGui::BeginPopupContextItem("ydsa", ImGuiMouseButton_Left)) {
            for (auto&[name, mat]: list)
                if (ImGui::MenuItem(name.c_str())) {
                    component.material = mat;
                }
            ImGui::EndPopup();
        }

        ImGui::BeginPopup("##Material");
        if (ImGui::BeginPopupModal("##Material", NULL)) {
            if (ImGui::MenuItem("Delete"))
                entity.RemoveComponent<MaterialComponent>();

            ImGui::EndPopup();
        }
        ImGui::PopID();
    }

    void ComponentView::ShowProperties(Entity entity, DrawableComponent &component) {
    }

    void ComponentView::ShowProperties(Entity entity, CameraComponent &component) {
        ImGui::DragFloat("FOV", &component.camera->GetSpec().fov, 1.0f, 0.0f, 360.0f, "%f");
        ImGui::DragFloat("Near", &component.camera->GetSpec().Near, 0.1f, 0.0f, 1.0f, "%.3f");
        ImGui::DragFloat("Far", &component.camera->GetSpec().Far, 0.5f, 1.0f, 1000.0f, "%.3f");
        ImGui::Checkbox("Primary", &component.primary);
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete"))
                entity.RemoveComponent<CameraComponent>();

            ImGui::EndPopup();
        }
    }

    void ComponentView::ShowProperties(Entity entity, MeshComponent &component) {
        ImGui::Text("Type %s", MeshTypeToString(component.type).c_str());
        if (component.type == MeshType::None) {
            ImGui::Text("No data");
            ImGui::SameLine();
            bool clicked = ImGui::Button("Create Mesh");
            if (ImGui::BeginPopupContextItem("ydsa", ImGuiMouseButton_Left)) {
                if (ImGui::MenuItem("Quad")) {
                    component = MeshComponent::Generate(entity, MeshType::Quad);
                }
                if (ImGui::MenuItem("Triangle")) {
                    component = MeshComponent::Generate(entity, MeshType::Triangle);
                }
                if (ImGui::MenuItem("Cube")) {
                    component = MeshComponent::Generate(entity, MeshType::Cube);
                }
                ImGui::EndPopup();
            }
        }
    }

    void ComponentView::ShowProperties(Entity entity, LightComponent &component) {
        ImGui::PushID(component.id());

        DrawVec3Control("Position", component.position, 1);

        ImGui::ColorEdit3("Ambient", &component.ambientColor.r);
        ImGui::ColorEdit3("Diffuse", &component.diffuseColor.r);
        ImGui::ColorEdit3("Specular", &component.specularColor.r);

        ImGui::DragFloat("Intensity", &component.intensity, 0.02, 0.0f, 1.0f, "%f");

        entity.GetComponent<TransformComponent>().position = component.position;

        ImGui::PopID();
    }

    void ComponentView::ShowProperties(Entity entity, TextureComponent &component) {
        ImGui::PushID(component.id());

        bool textureLoadNeeded = false;
        /*  int state = LoadAndDrawTexture(entity, component.name, entity.m_Scene->GetTexture(component.name));

          switch (state) {
          case 0:
              break;
          case 1:
              textureLoadNeeded = true;
              break;
          case 2:
              entity.m_Scene->RemoveTexture(component.name);
              break;
          }*/

        if (textureLoadNeeded) {
            std::string texturePath = FileDialogs::OpenFile(Application::Get().WindowHandle()->GetHandle(),
                                                            "All Files\0*.*\0\0").string();

            if (texturePath.size() > 0) {
                std::string textureName = std::filesystem::path(texturePath).filename().string();
                component.name = textureName;

                entity.m_Scene->AddTexture(textureName, Texture::Create(texturePath));
            }
            textureLoadNeeded = false;
        }

        ImGui::PopID();
    }

    bool
    ComponentView::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth) {
        bool modified = false;

        const ImGuiIO &io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize)) {
            values.x = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize)) {
            values.y = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize)) {
            values.z = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return modified;
    }

    bool
    ComponentView::DrawVec4Control(const std::string &label, glm::vec4 &values, float resetValue, float columnWidth) {
        bool modified = false;

        const ImGuiIO &io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize)) {
            values.x = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize)) {
            values.y = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize)) {
            values.z = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.4f, 0.05f, 0.075f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.45f, 0.1f, 0.1f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.4f, 0.05f, 0.075f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("W", buttonSize)) {
            values.w = resetValue;
            modified = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modified |= ImGui::DragFloat("##W", &values.w, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return modified;
    }

    int ComponentView::LoadAndDrawTexture(Entity entity, const std::string &label, Ref<Texture> &texture) {
        ImGui::Separator();

        ImGui::Text("%s", label.c_str());

        if (texture) {
            if (texture->GetState() == TextureState::Loaded) {
                ImGui::Image((void *) texture->ID(), ImVec2{200, 200});
                ImGui::SameLine();
                if (ImGui::Button("Remove")) {
                    return 2;
                }
            }
        } else {
            if (ImGui::Button("Load Texture")) {
                std::string texturePath = FileDialogs::OpenFile(Application::Get().WindowHandle()->GetHandle(),
                                                                "All Files\0*.*\0\0").string();

                if (texturePath.size() > 0) {
                    std::string textureName = std::filesystem::path(texturePath).filename().string();

                    texture = Texture::Create(texturePath);
                }
                return 1;
            }
        }

        return 0;
    }
}