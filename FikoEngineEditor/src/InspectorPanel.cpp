#include "InspectorPanel.h"

void InspectorPanel::OnImGUIRender(FikoEngine::Scene* scene, WeakRef<FikoEngine::Window> window) {
    using namespace FikoEngine;
    ImGui::Begin("Inspector");
    {
        if(scene && scene->GetSelectedEntity().IsValid()) {
            Entity selectedEntity = scene->GetSelectedEntity();

            AddComponentsMenu(selectedEntity);

            ShowComponent<TagComponent>("Tag Component",selectedEntity,window,false,false);
            ShowComponent<TransformComponent>("Transform Component",selectedEntity,window);
            ShowComponent<MaterialComponent>("Material Component",selectedEntity,window);
            ShowComponent<CameraComponent>("Camera Component",selectedEntity,window);
            ShowComponent<MeshComponent>("Mesh Component",selectedEntity,window);
            ShowComponent<LightComponent>("Light Component",selectedEntity,window);
            ShowComponent<TextureComponent>("Texture Component",selectedEntity,window);

        }
        ImGui::End();
    }
}
void InspectorPanel::AddComponentsMenu(FikoEngine::Entity entity){
    using namespace FikoEngine;
    if (ImGui::BeginPopupContextWindow(nullptr, 1)) {
        if (ImGui::BeginMenu("Add")) {
            if (ImGui::MenuItem("Add Transform")) {
                if (!entity.HasComponent<TransformComponent>())
                    entity.AddComponent<TransformComponent>();
            }
            if (ImGui::MenuItem("Add Material")) {
                if (!entity.HasComponent<MaterialComponent>())
                    entity.AddComponent<MaterialComponent>();
            }
            if (ImGui::MenuItem("Add Mesh")) {
                if (!entity.HasComponent<MeshComponent>())
                    entity.AddComponent<MeshComponent>().GetComponent<MeshComponent>() = MeshComponent::Generate(MeshType::None);
            }
            if (ImGui::MenuItem("Add Camera Component")) {
                if (!entity.HasComponent<CameraComponent>())
                    entity.AddComponent<CameraComponent>();
            }
            if (ImGui::MenuItem("Add Light Component")) {
                if (!entity.HasComponent<LightComponent>())
                    entity.AddComponent<LightComponent>();
            }
            if (ImGui::MenuItem("Add Texture Component")) {
                if (!entity.HasComponent<TextureComponent>())
                    entity.AddComponent<TextureComponent>();
            }
            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }
}
template <typename T>
void InspectorPanel::ShowComponent(std::string_view Title,FikoEngine::Entity entity, WeakRef<FikoEngine::Window> window,bool allowDeleteOption,bool allowOpenOption){
    using namespace FikoEngine;
    bool opened{},deleted{};
    if (entity.HasComponent<T>()) {
        ImGui::Separator();

        if(allowOpenOption){
            opened = ImGui::TreeNodeEx(Title.data(),
                                       ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen);
        }

        if (allowDeleteOption && ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete"))
                deleted = true;
            ImGui::EndPopup();
        }
        if (opened && allowOpenOption) {
            ComponentView::ShowProperties(entity,entity.GetComponent<T>(),window);
            ImGui::TreePop();
        }else if(!allowOpenOption){
            ComponentView::ShowProperties(entity,entity.GetComponent<T>(),window);
        }
        if (deleted) {
            entity.RemoveComponent<T>();
        }
    }
}
