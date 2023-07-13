#include "AssetsPanel.hpp"

AssetsPanel::AssetsPanel(std::filesystem::path assetsDirectory) {
    m_AssetsDirectory = assetsDirectory;
    m_CurrentDirectory = assetsDirectory;

    m_Icons.emplace(FikoEngine::File::Type::Generic  , FikoEngine::Texture::CreateRaw(m_AssetsDirectory.string() + "/Icons/File.png"));
    m_Icons.emplace(FikoEngine::File::Type::Directory, FikoEngine::Texture::CreateRaw(m_AssetsDirectory.string() + "/Icons/Directory.png"));
}

void AssetsPanel::LoadDirectory(std::filesystem::path path) {
    m_CurrentDirectory = std::move(path);
}

void AssetsPanel::OnImGUIRender(FikoEngine::Scene** scene) {
    ImGui::Begin("Assets");

    uint32_t width = (uint32_t)ImGui::GetContentRegionAvail().x;
    uint32_t cellSize = m_Padding + m_IconSize;
    m_NumIconsPerRow = width / cellSize;

    if (m_NumIconsPerRow < 1)
        m_NumIconsPerRow = 1;

    if (std::filesystem::absolute(m_CurrentDirectory).compare(m_AssetsDirectory) > 0) {
        ImGui::Button("<--");
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }
    ImGui::Columns((int)m_NumIconsPerRow, nullptr, false);

    std::vector<std::filesystem::directory_entry> files;
    std::vector<std::filesystem::directory_entry> folders;
    for (const auto &entry: std::filesystem::directory_iterator(m_CurrentDirectory)) {
        if (entry.is_directory()) {
            folders.emplace_back(entry);
        } else {
            files.emplace_back(entry);
        }
    }

    for (const auto &entry: folders) {
        ImGui::PushID(entry.path().filename().string().c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton((void *) m_Icons[FikoEngine::File::Type::Directory]->ID(), ImVec2((float)m_IconSize, (float)m_IconSize), {0, 1}, {1, 0});
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (entry.is_directory()) {
                m_CurrentDirectory = entry.path();
            }
        }

        ImGui::TextWrapped(entry.path().filename().string().c_str());

        ImGui::NextColumn();
        ImGui::PopID();
    }

    for (const auto &entry: files) {
        ImGui::PushID(entry.path().filename().string().c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton((void *) m_Icons[FikoEngine::File::Type::Generic]->ID(), ImVec2((float)m_IconSize, (float)m_IconSize), {0, 1}, {1, 0});
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (entry.is_directory()) {
                m_CurrentDirectory = entry.path();
            }else{
                if (entry.path().extension() == ".yaml") {
                    FikoEngine::Scene* newScene = FikoEngine::SceneSerializer::Deserialize(entry.path().string());
                    if(newScene) {
                        delete *scene;
                        *scene = newScene;
                    }
                }
            }
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

AssetsPanel::~AssetsPanel() {
    LOG_INFO("AssetsPanel Destroy");

    for(auto& [type,icon] : m_Icons){
        delete icon;
    }
    m_Icons.clear();
}
