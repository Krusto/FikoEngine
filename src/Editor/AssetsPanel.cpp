#include "IconsFontAwesome6.h"

#include "AssetsPanel.h"
#include <Renderer/Renderer.h>
#include <imgui.h>

#include <iostream>
#include <Core/File.h>

AssetsPanel::AssetsPanel(Ref<Window> window, Scene* scene, std::filesystem::path path)
    :m_Scene(scene), m_Window(window->GetHandle()), m_AssetsDirectory(path), m_CurrentDirectory(path) 
{
    
    m_Icons.emplace("Directory", Texture::Create(m_AssetsDirectory.string() + "/Icons/Directory.png"));
    m_Icons.emplace("File", Texture::Create(m_AssetsDirectory.string() + "/Icons/File.png"));
}

void AssetsPanel::OnImGUIRender()
{
    ImGui::Begin("Assets"); {
        uint32_t width = ImGui::GetContentRegionAvail().x;

        m_NumIconsPerRow = width / (m_IconSize+m_Padding);

        if (m_CurrentDirectory != m_AssetsDirectory) {
            if (ImGui::Button("<--")) {
                m_CurrentDirectory = m_CurrentDirectory.parent_path();
            }
        }

        ImGui::Columns(m_NumIconsPerRow,0,false);

        
        std::vector<std::filesystem::path> directoryEntries[2];

        for (const auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
            if (directoryEntry.is_directory()) {
                directoryEntries[0].emplace_back(directoryEntry.path());
            }
            else {
                directoryEntries[1].emplace_back(directoryEntry.path());
            }
        }

        for (size_t i = 0; i < 2; i++)
        {
            auto& currentList = directoryEntries[i];
            Ref<Texture> icon = (i == 0 ? m_Icons["Directory"] : m_Icons["File"]);
            File::Type type = (File::Type)(i+1);

            for (auto& path : currentList) {
                std::string filenameString = path.filename().string();

                ImGui::PushID(filenameString.c_str());
                
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

                ImGui::ImageButton((void*)icon->ID(), ImVec2(m_IconSize, m_IconSize), { 0.0, 1.0 }, { 1.0, 0.0 }, 0);

                if (ImGui::BeginDragDropSource())
                {
                    auto relativePath = std::filesystem::relative(path, m_AssetsDirectory);
                    const wchar_t* itemPath = relativePath.c_str();
                    ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
                    ImGui::EndDragDropSource();
                }

                ImGui::PopStyleColor();

                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    if (type == File::Type::Directory)
                        m_CurrentDirectory /= path.filename();

                }
                ImGui::TextWrapped(filenameString.c_str());

                ImGui::NextColumn();
                ImGui::PopID();
            }
        }

        ImGui::Columns(1);

        ImGui::SliderInt("Icon Size", (int*)&m_IconSize, 16, 1024);
        ImGui::SliderInt("Padding",(int*)&m_Padding,0,32);
        ImGui::End();
    }
}

void AssetsPanel::LoadDirectory(std::filesystem::path path)
{
    m_AssetsDirectory = std::filesystem::absolute(path);
    m_CurrentDirectory = std::filesystem::absolute(path);
}
