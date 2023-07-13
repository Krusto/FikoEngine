#pragma once
#include <FikoEngine.h>

class HierarchyPanel : public RefCounted{
public:
    HierarchyPanel();
    explicit HierarchyPanel(WeakRef<FikoEngine::Window> window) : m_Window(window) {}
    ~HierarchyPanel() = default;

    void OnImGUIRender(FikoEngine::Scene* scene);

private:
    void ListEntities(FikoEngine::UUID entityID, FikoEngine::Scene* scene);
    void DrawEntityNode(FikoEngine::Entity entity, FikoEngine::Scene* scene);

    WeakRef<FikoEngine::Window> m_Window;
    FikoEngine::Entity m_SelectedEntity;

};
