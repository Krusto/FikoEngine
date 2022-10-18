#pragma once
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>
namespace FikoEngine {

    class HierarchyPanel {
    public:
        HierarchyPanel() = default;

        HierarchyPanel(Scene *scene) : m_Scene(scene) {}

        void OnImGUIRender();

    private:
        void ListEntities(UUID entityID, Scene *scene);

        void DrawEntityNode(Entity entity);

        Scene *m_Scene;
        Entity m_SelectedEntity;

    };
}