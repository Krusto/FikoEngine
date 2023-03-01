#pragma once
#include <filesystem>
#include <Core/Ref.h>
#include <Core/Window.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>

class AssetsPanel {
public:
    AssetsPanel() = default;
    AssetsPanel(Ref<Window> window, Scene* scene, std::filesystem::path path);
    void OnImGUIRender();
    void LoadDirectory(std::filesystem::path path);
private:
    std::filesystem::path m_CurrentDirectory;
    std::filesystem::path m_AssetsDirectory;

    uint32_t m_IconSize = 128;
    uint32_t m_Padding = 0;

    uint32_t m_NumIconsPerRow;
    Scene* m_Scene;
    GLFWwindow* m_Window;
    Entity m_SelectedEntity;
  
    std::unordered_map<std::string_view, Ref<Texture>> m_Icons;
};