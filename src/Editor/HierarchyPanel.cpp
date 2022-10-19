#include "HierarchyPanel.h"
#include <imgui.h>
#include <Scene/Component.h>
#include <Scene/Entity.h>
#include <ImGUI/ImGUILayer.h>

namespace FikoEngine {

    void HierarchyPanel::OnImGUIRender() {
        ImGui::Begin("Hierarchy");
        {
            if (ImGui::BeginPopupContextWindow()) {
                if (ImGui::BeginMenu("Create")) {
                    if (ImGui::MenuItem("Empty Entity")) {
                        m_SelectedEntity = m_Scene->AddEntity("Empty Entity");
                    }
                    if (ImGui::MenuItem("Camera")) {
                        m_SelectedEntity = m_Scene->AddEntity("New Camera");
                        m_SelectedEntity
                                .AddComponent<CameraComponent>()
                                .AddComponent<TransformComponent>()
                                .GetComponent<CameraComponent>().camera = Ref<Camera>::Create(
                                CameraSpec(m_Scene->GetViewport(), 90.0));
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }
            for (auto entity: m_Scene->GetEntitiesWith<IDComponent, RelationshipComponent>()) {
                Entity e(entity, m_Scene);
                if (e.HasParents() == 0)
                    DrawEntityNode({entity, m_Scene});
            }


            ImGui::End();
        }
    }

    void HierarchyPanel::DrawEntityNode(Entity entity) {
        std::string Tag;
        if (entity.HasComponent<TagComponent>())
            Tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags =
                (entity == m_SelectedEntity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        if (entity.HasChildren() == false)
            flags |= ImGuiTreeNodeFlags_Leaf;

        const bool opened = ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) entity, flags, Tag.c_str());
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            m_SelectedEntity = entity;
            m_Scene->SetSelectedEntity(entity);
        }

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete"))
                entityDeleted = true;

            ImGui::EndPopup();
        }


        if (opened) {
            for (auto &child: entity.GetChildren()) {
                Entity e = m_Scene->GetEntity(child);
                if (e)
                    DrawEntityNode(e);
            }

            ImGui::TreePop();
        }

        if (entityDeleted) {
            m_Scene->RemoveEntity(entity);
            if (entity == m_SelectedEntity) {
                m_Scene->SetSelectedEntity({});
                m_SelectedEntity = {};
            }
        }

    }

    void HierarchyPanel::ListEntities(UUID entityID, Scene *scene) {

        if (entityID != scene->GetID()) {
            std::string Tag = scene->GetEntity(entityID).GetComponent<TagComponent>().Tag;

            if (scene->GetEntity(entityID).HasChildren()) {
                if (ImGui::TreeNodeEx(Tag.c_str(), ImGuiTreeNodeFlags_OpenOnArrow)) {
                    std::vector<UUID> Children = scene->GetEntity(entityID).GetChildren();
                    for (auto &ChildID: Children) {
                        ListEntities(ChildID, scene);
                    }
                    ImGui::TreePop();
                }
            } else {
                ImGui::PushID(ImGui::NextID());

                bool item_selected{};
                if (ImGui::Selectable(Tag.c_str(), item_selected)) {
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                    }
                    ImGui::SetItemDefaultFocus();
                }

                ImGui::PopID();
            }
        } else {
            std::string Tag = scene->GetHandle().GetComponent<TagComponent>().Tag;
            if (scene->GetHandle().HasChildren()) {
                if (ImGui::TreeNodeEx(Tag.c_str(), ImGuiTreeNodeFlags_OpenOnArrow)) {
                    std::vector<UUID> Children = scene->GetHandle().GetChildren();
                    for (auto &ChildID: Children) {
                        ListEntities(ChildID, scene);
                    }
                    ImGui::TreePop();
                }
            } else {
                ImGui::Text("%s", Tag.c_str());
            }
        }
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            scene->SetSelectedEntity(scene->GetEntity(entityID));
        }
    }

}