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

        uint32_t m_IconSize{80};
        uint32_t m_NumIconsPerRow{1};
        uint32_t m_Padding{10};

        Scene* m_Scene{};
        Entity* m_Entity{};
        Ref<Window> m_Window;
        std::unordered_map<File::Type,Ref<Texture>> m_Icons;

    };
}
