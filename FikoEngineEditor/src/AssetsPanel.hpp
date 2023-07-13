#pragma once
#include <filesystem>
#include <FikoEngine.h>

class AssetsPanel : public RefCounted{
public:
    AssetsPanel() = default;
    ~AssetsPanel();

    AssetsPanel(std::filesystem::path assetsDirectory);

    void LoadDirectory(std::filesystem::path path);
    void OnImGUIRender(FikoEngine::Scene** scene);
private:
    std::filesystem::path m_AssetsDirectory;
    std::filesystem::path m_CurrentDirectory;

    uint32_t m_IconSize{80};
    uint32_t m_NumIconsPerRow{1};
    uint32_t m_Padding{10};

    std::unordered_map<FikoEngine::File::Type,FikoEngine::Texture*> m_Icons;

};
