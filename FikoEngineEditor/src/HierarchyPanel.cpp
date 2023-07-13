#include "HierarchyPanel.h"


HierarchyPanel::HierarchyPanel() {
    m_SelectedEntity = {(uint32_t)entt::null,nullptr};
}
void HierarchyPanel::OnImGUIRender(FikoEngine::Scene* scene) {
    ImGui::Begin("Hierarchy");
    {
        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::BeginMenu("Create")) {
                if (ImGui::MenuItem("Empty Entity")) {
                    m_SelectedEntity = scene->AddEntity("Empty Entity");
                }
                if (ImGui::MenuItem("Camera")) {
                    m_SelectedEntity = scene->AddEntity("New Camera");
                    m_SelectedEntity
                            .AddComponent<FikoEngine::CameraComponent>()
                            .AddComponent<FikoEngine::TransformComponent>()
                            .GetComponent<FikoEngine::CameraComponent>().camera = Ref<FikoEngine::Camera>::Create(
                            FikoEngine::CameraSpec(scene->GetViewport(), 90.0));
                }
                if (ImGui::MenuItem("Load Object")) {

                    //std::string fileName = FileDialogs::OpenFile(m_Window->GetHandle(),
                    //                                             "All Files\0*.*\0\0").string();


                }
                ImGui::EndMenu();

        }
        ImGui::EndPopup();
        }

        if(scene) {
            DrawEntityNode(scene->GetHandle(), scene);
        }
        ImGui::End();
    }
}

void HierarchyPanel::DrawEntityNode(FikoEngine::Entity entity, FikoEngine::Scene* scene) {
    std::string Tag;
    if (entity.HasComponent<FikoEngine::TagComponent>())
        Tag = entity.GetComponent<FikoEngine::TagComponent>().Tag;

    ImGuiTreeNodeFlags flags = (entity == m_SelectedEntity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

    if (entity.HasChildren() == false)
        flags |= ImGuiTreeNodeFlags_Leaf;

    const bool opened = ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) entity, flags, Tag.c_str());
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        m_SelectedEntity = entity;
        scene->SetSelectedEntity(entity);
    }

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem("Delete"))
            entityDeleted = true;

        ImGui::EndPopup();
    }


    if (opened) {
        auto children = entity.GetChildren();

        for (const auto& child: entity.GetChildren()) {
            FikoEngine::Entity e = scene->GetEntity(child);
            if(e.IsValid())
                DrawEntityNode(e,scene);
        }

        ImGui::TreePop();
    }

    if (entityDeleted) {
        scene->RemoveEntity(entity);
        if (entity == m_SelectedEntity) {
            scene->SetSelectedEntity({});
            m_SelectedEntity = {};
        }
    }

}

void HierarchyPanel::ListEntities(FikoEngine::UUID entityID, FikoEngine::Scene* scene) {

    if (entityID != scene->GetID()) {
        std::string Tag = scene->GetEntity(entityID).GetComponent<FikoEngine::TagComponent>().Tag;

        if (scene->GetEntity(entityID).HasChildren()) {
            if (ImGui::TreeNodeEx(Tag.c_str(), ImGuiTreeNodeFlags_OpenOnArrow)) {
                std::vector<FikoEngine::UUID> Children = scene->GetEntity(entityID).GetChildren();
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
        std::string Tag = scene->GetHandle().GetComponent<FikoEngine::TagComponent>().Tag;
        if (scene->GetHandle().HasChildren()) {
            if (ImGui::TreeNodeEx(Tag.c_str(), ImGuiTreeNodeFlags_OpenOnArrow)) {
                std::vector<FikoEngine::UUID> Children = scene->GetHandle().GetChildren();
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

