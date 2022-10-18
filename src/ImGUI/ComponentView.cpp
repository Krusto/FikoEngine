#include "ComponentView.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

void ComponentView::ShowProperties(Entity entity, TagComponent& component)
{
    auto& tag = component.Tag;
    std::string buffer = std::string(256, NULL);
    std::memcpy(&buffer[0], &tag[0], tag.size());
    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
    if (ImGui::InputText("##Tag", &buffer[0], buffer.size()))
    {
        tag = buffer;
    }
    ImGui::PopItemWidth();
}

void ComponentView::ShowProperties(Entity entity, TransformComponent& component)
{
    DrawVec3Control("Translation", component.position);
    DrawVec3Control("Rotation", component.rotation);
    DrawVec3Control("Scale", component.size, 1.0f);
   
}

void ComponentView::ShowProperties(Entity entity, MaterialComponent& component)
{
    if (component.material) {
        ImGui::Text("Material name: %s", component.material->GetName().c_str());
        const auto& buffer = (*component.material->GetShader()->GetShaderBuffers().begin()).second;
        const auto& uniforms = buffer.Uniforms;

        for (const auto& uniform : uniforms) {
            auto type = uniform.second.m_Type;
            if (type == ShaderUniformType::Vec3) {
                auto& value = component.material->GetVector3(uniform.first);
                DrawVec3Control(uniform.first, value, 1);
            }
            if (type == ShaderUniformType::Vec4) {

                auto& value = component.material->GetVector4(uniform.first);
                ImGui::Text("%s", uniform.first.c_str());
                ImGui::SameLine();
                ImGui::ColorEdit4("", &value.r);
            }
        }
    }
    else {
        ImGui::Text("%s", "No material type added");
    }
    auto& list = entity.m_Scene->GetMaterials();

    bool clicked = ImGui::Button("Select material");
    if (ImGui::BeginPopupContextItem("ydsa", ImGuiMouseButton_Left)) {
        for (auto& [name, mat] : list)
            if (ImGui::MenuItem(name.c_str())) {
                component.material = mat;
            }
        ImGui::EndPopup();
    }

    ImGui::BeginPopup("##Material");
    if (ImGui::BeginPopupModal("##Material",NULL))
    {
        if (ImGui::MenuItem("Delete"))
            entity.RemoveComponent<MaterialComponent>();
        
        ImGui::EndPopup();
    }
}

void ComponentView::ShowProperties(Entity entity, DrawableComponent& component)
{
}

void ComponentView::ShowProperties(Entity entity, CameraComponent& component)
{
    ImGui::DragFloat("FOV", &component.camera->GetSpec().fov, 1.0f, 0.0f, 360.0f, "%f");
    ImGui::DragFloat("Near", &component.camera->GetSpec().Near, 0.1f, 0.0f, 1.0f, "%.3f");
    ImGui::DragFloat("Far", &component.camera->GetSpec().Far, 0.5f, 1.0f, 1000.0f, "%.3f");
    ImGui::Checkbox("Primary", &component.primary);
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete"))
            entity.RemoveComponent<CameraComponent>();

        ImGui::EndPopup();
    }
}
void ComponentView::ShowProperties(Entity entity, MeshComponent& component)
{
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
            ImGui::EndPopup();
        }
    }
}
bool ComponentView::DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
{
    bool modified = false;

    const ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
    {
        values.x = resetValue;
        modified = true;
    }

    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
    {
        values.y = resetValue;
        modified = true;
    }

    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
    {
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

bool ComponentView::DrawVec4Control(const std::string& label, glm::vec4& values, float resetValue, float columnWidth)
{
    bool modified = false;

    const ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
    {
        values.x = resetValue;
        modified = true;
    }

    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
    {
        values.y = resetValue;
        modified = true;
    }

    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
    {
        values.z = resetValue;
        modified = true;
    }

    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    modified |= ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.4f, 0.05f, 0.075f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.45f, 0.1f, 0.1f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.4f, 0.05f, 0.075f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("W", buttonSize))
    {
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
