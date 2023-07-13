#pragma once
#include <FikoEngine.h>

class InspectorPanel : public RefCounted {
public:
    InspectorPanel() = default;
    ~InspectorPanel() = default;

    void OnImGUIRender(FikoEngine::Scene* scene, WeakRef<FikoEngine::Window> window);
private:
    void AddComponentsMenu(FikoEngine::Entity entity);
    template <typename T>
    void ShowComponent(std::string_view Title,FikoEngine::Entity entity, WeakRef<FikoEngine::Window> window,bool allowDeleteOption = true,bool allowOpenOption = true);
};
