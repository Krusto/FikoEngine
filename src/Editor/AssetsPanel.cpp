#include "AssetsPanel.hpp"
#include <imgui.h>

FikoEngine::AssetsPanel::AssetsPanel(Ref<Window> window, FikoEngine::Scene *scene,
                                     std::filesystem::path assetsDirectory) {
    m_Window = window;
    m_Scene = scene;
    m_AssetsDirectory = assetsDirectory;
    m_CurrentDirectory = assetsDirectory;

    m_Icons.emplace(File::Type::Generic, Texture::Create(assetsDirectory.string()+"/Icons/File.png"));
    m_Icons.emplace(File::Type::Directory, Texture::Create(assetsDirectory.string()+"/Icons/Directory.png"));
}

void FikoEngine::AssetsPanel::LoadDirectory(std::filesystem::path path) {
    m_CurrentDirectory = path;
}

void FikoEngine::AssetsPanel::OnImGUIRender() {
    ImGui::Begin("Assets");

    u32 width = ImGui::GetContentRegionAvail().x;
    u32 cellSize = m_Padding + m_IconSize;
    m_NumIconsPerRow = width / cellSize;

    if(m_NumIconsPerRow < 1)
        m_NumIconsPerRow = 1;

    if(std::filesystem::absolute(m_CurrentDirectory).compare(m_AssetsDirectory) > 0){
        ImGui::Button("<--");
        if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)){
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }
    ImGui::Columns(m_NumIconsPerRow,nullptr,false);

    std::vector<std::filesystem::directory_entry> files;
    std::vector<std::filesystem::directory_entry> folders;
    for (const auto & entry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
        if(entry.is_directory()){
            folders.emplace_back(entry);
        }else{
            files.emplace_back(entry);
        }
    }

    Ref<Texture> icon = m_Icons[File::Type::Directory];

    for(const auto& entry : folders) {
        ImGui::PushID(entry.path().filename().string().c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton((void *) icon->ID(), ImVec2(m_IconSize, m_IconSize), {0, 1}, {1, 0});
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (entry.is_directory())
                m_CurrentDirectory = entry.path();
        }

        ImGui::TextWrapped(entry.path().filename().string().c_str());

        ImGui::NextColumn();
        ImGui::PopID();
    }

    icon = m_Icons[File::Type::Generic];

    for(const auto& entry : files) {
        ImGui::PushID(entry.path().filename().string().c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton((void *) icon->ID(), ImVec2(m_IconSize, m_IconSize), {0, 1}, {1, 0});
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (entry.is_directory())
                m_CurrentDirectory = entry.path();
        }

        ImGui::TextWrapped(entry.path().filename().string().c_str());

        ImGui::NextColumn();
        ImGui::PopID();
    }
    ImGui::Columns(1);
    ImGui::SliderInt("Icon Size", reinterpret_cast<int *>(&m_IconSize), 0, 512);
    ImGui::SliderInt("Padding", reinterpret_cast<int *>(&m_Padding), 0, 32);
    ImGui::End();
}
