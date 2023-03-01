#include <Editor/InspectorPanel.h>
#include <ImGUI/ComponentView.h>
#include <imgui.h>
namespace FikoEngine {

    void InspectorPanel::OnImGUIRender(Entity selectedEntity) {
        ImGui::Begin("Inspector");
        {
            if (selectedEntity.IsValid()) {
                if (ImGui::BeginPopupContextWindow(nullptr, 1)) {
                    if (ImGui::BeginMenu("Add")) {
                        if (ImGui::MenuItem("Add Transform")) {
                            if (!selectedEntity.HasComponent<TransformComponent>())
                                selectedEntity.AddComponent<TransformComponent>();
                        }
                        if (ImGui::MenuItem("Add Material")) {
                            if (!selectedEntity.HasComponent<MaterialComponent>())
                                selectedEntity.AddComponent<MaterialComponent>();
                        }
                        if (ImGui::MenuItem("Add Mesh")) {
                            if (!selectedEntity.HasComponent<MeshComponent>())
                                selectedEntity.AddComponent<MeshComponent>().GetComponent<MeshComponent>() = MeshComponent::Generate(
                                        selectedEntity, MeshType::None);
                        }
                        if (ImGui::MenuItem("Add Camera Component")) {
                            if (!selectedEntity.HasComponent<CameraComponent>())
                                selectedEntity.AddComponent<CameraComponent>();
                        }
                        if (ImGui::MenuItem("Add Light Component")) {
                            if (!selectedEntity.HasComponent<LightComponent>())
                                selectedEntity.AddComponent<LightComponent>();
                        }
                        if (ImGui::MenuItem("Add Texture Component")) {
                            if (!selectedEntity.HasComponent<TextureComponent>())
                                selectedEntity.AddComponent<TextureComponent>();
                        }
                        ImGui::EndMenu();
                    }
                    ImGui::EndPopup();
                }

                bool deleted = false;
                bool opened = false;
                if (selectedEntity.HasComponent<TagComponent>()) {
                    ImGui::Separator();
                    ComponentView::ShowProperties(selectedEntity, selectedEntity.GetComponent<TagComponent>());
                }
                if (selectedEntity.HasComponent<TransformComponent>()) {
                    ImGui::Separator();
                    opened = ImGui::TreeNodeEx("Transform Component",
                                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete"))
                            deleted = true;
                        ImGui::EndPopup();
                    }
                    if (opened) {
                        ComponentView::ShowProperties(selectedEntity,
                                                      selectedEntity.GetComponent<TransformComponent>());
                        ImGui::TreePop();
                    }
                    if (deleted) {
                        selectedEntity.RemoveComponent<TransformComponent>();
                        deleted = false;
                    }
                }
                if (selectedEntity.HasComponent<MaterialComponent>()) {
                    ImGui::Separator();
                    opened = ImGui::TreeNodeEx("Material Component",
                                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete"))
                            deleted = true;
                        ImGui::EndPopup();
                    }
                    if (opened) {
                        ComponentView::ShowProperties(selectedEntity, selectedEntity.GetComponent<MaterialComponent>());
                        ImGui::TreePop();
                    }
                    if (deleted) {
                        selectedEntity.RemoveComponent<MaterialComponent>();
                        deleted = false;
                    }
                }
                if (selectedEntity.HasComponent<CameraComponent>()) {
                    ImGui::Separator();
                    opened = ImGui::TreeNodeEx("Camera Component",
                                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete"))
                            deleted = true;
                        ImGui::EndPopup();
                    }
                    if (opened) {
                        ComponentView::ShowProperties(selectedEntity, selectedEntity.GetComponent<CameraComponent>());
                        ImGui::TreePop();
                    }
                    if (deleted) {
                        selectedEntity.RemoveComponent<CameraComponent>();
                        deleted = false;
                    }
                }
                if (selectedEntity.HasComponent<MeshComponent>()) {
                    ImGui::Separator();
                    opened = ImGui::TreeNodeEx("Mesh Component",
                                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete"))
                            deleted = true;
                        ImGui::EndPopup();
                    }
                    if (opened) {
                        ComponentView::ShowProperties(selectedEntity, selectedEntity.GetComponent<MeshComponent>());
                        ImGui::TreePop();
                    }
                    if (deleted) {
                        selectedEntity.RemoveComponent<MeshComponent>();
                        deleted = false;
                    }
                }
                if (selectedEntity.HasComponent<LightComponent>()) {
                    ImGui::Separator();
                    opened = ImGui::TreeNodeEx("Light Component",
                                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete"))
                            deleted = true;
                        ImGui::EndPopup();
                    }
                    if (opened) {
                        ComponentView::ShowProperties(selectedEntity, selectedEntity.GetComponent<LightComponent>());
                        ImGui::TreePop();
                    }
                    if (deleted) {
                        selectedEntity.RemoveComponent<LightComponent>();
                        deleted = false;
                    }
                }
                if (selectedEntity.HasComponent<TextureComponent>()) {
                    ImGui::Separator();
                    opened = ImGui::TreeNodeEx("Texture Component",
                                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete"))
                            deleted = true;
                        ImGui::EndPopup();
                    }
                    if (opened) {
                        ComponentView::ShowProperties(selectedEntity, selectedEntity.GetComponent<TextureComponent>());
                        ImGui::TreePop();
                    }
                    if (deleted) {
                        selectedEntity.RemoveComponent<TextureComponent>();
                        deleted = false;
                    }
                }
            }
            ImGui::End();
        }
    }
}
