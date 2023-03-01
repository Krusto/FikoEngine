#pragma once
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>
#include <Renderer/Window.h>
namespace FikoEngine {

    class HierarchyPanel {
    public:
        HierarchyPanel() = default;

        HierarchyPanel(Scene *scene,Ref<Window> window) : m_Scene(scene),m_Window(window) {}
        HierarchyPanel(const HierarchyPanel& other) = default;

        HierarchyPanel& operator=(const HierarchyPanel& other){
            this->m_Scene = other.m_Scene;
            this->m_SelectedEntity = other.m_SelectedEntity;

            return *this;
        };
        void OnImGUIRender();

    private:
        void ListEntities(UUID entityID, Scene *scene);

        void DrawEntityNode(Entity entity);

        Scene *m_Scene;
        Ref<Window> m_Window;
        Entity m_SelectedEntity;

    };
}