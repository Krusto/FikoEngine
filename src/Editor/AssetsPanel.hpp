#pragma once

#include <filesystem>
#include "Renderer/Window.h"
#include "Scene/Entity.h"
#include "Util/File.h"

namespace FikoEngine{
    class AssetsPanel{
    public:
        AssetsPanel() = default;
        AssetsPanel(Ref<Window> window,Scene* scene,std::filesystem::path assetsDirectory);
        void LoadDirectory(std::filesystem::path path);
        void OnImGUIRender();
    private:
        std::filesystem::path m_AssetsDirectory;
        std::filesystem::path m_CurrentDirectory;

        u32 m_IconSize{80};
        u32 m_NumIconsPerRow{1};
        u32 m_Padding{10};

        Scene* m_Scene{};
        Entity* m_Entity{};
        Ref<Window> m_Window;
        std::unordered_map<File::Type,Ref<Texture>> m_Icons;

    };
}
