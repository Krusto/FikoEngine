#pragma once
#include <Core/Ref.h>
#include <Core/UUID.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>
namespace FikoEngine {

    class InspectorPanel {
    public:
        InspectorPanel() = default;

        InspectorPanel(Scene *scene) : m_Scene(scene) {}

        void OnImGUIRender(Entity selectedEntity);

    private:
        Scene *m_Scene;
    };
}