//
// Created by Brandon Boudreaux on 3/21/23.
//

#include "Editor.h"

PhyG::Editor::Editor(lua_State * L) {
    lua = L;
    title = "Lua Editor";
}

PhyG::Editor::~Editor() {}

void PhyG::Editor::RecurseDrawFiles(std::filesystem::path p){
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        if(entry.is_directory()){
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if(ImGui::TreeNodeEx(entry.path().filename().c_str(), ImGuiTreeNodeFlags_SpanFullWidth)){
                ImGui::Separator();
                RecurseDrawFiles(entry.path().string());
                ImGui::TreePop();
            }
        }else{
            static std::unordered_map<std::string, bool> selected;
            selected.insert( {entry.path().string(), false} );
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            if(ImGui::Selectable(entry.path().filename().c_str(), &selected.find(entry.path().string())->second, ImGuiSelectableFlags_AllowDoubleClick)){
                if(ImGui::IsMouseDoubleClicked(0)){
                    tabs.insert( { entry.path() ,std::make_unique<Tab>(entry.path(), lua) } );
                    fe_open = false;
                }
            }
        }
    }
}

void PhyG::Editor::FileExplorer() {
    ImGui::OpenPopup("File Explorer");
    if(ImGui::BeginPopupModal("File Explorer", &fe_open)){

        ImGui::Text("Choose a file to open:");
        ImGui::Separator();

        ImVec2 size = ImGui::GetContentRegionAvail();

        ImGui::BeginTable("File", 1, fe_table_flags, ImVec2(size.x, size.y-30));
        ImGui::TableSetupColumn("File");
        ImGui::TableHeadersRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        if(ImGui::TreeNodeEx(default_path, ImGuiTreeNodeFlags_SpanFullWidth)){
            RecurseDrawFiles(default_path);
            ImGui::TreePop();
        }

        ImGui::EndTable();

        ImGui::Separator();
        ImGui::Button("Open");

        ImGui::EndPopup();
    }
}

void PhyG::Editor::Render() {
    if(!open){
        return;
    }

    ImGui::Begin(title, &open, flags);

    if(ImGui::BeginMenuBar()){

        if(ImGui::BeginMenu("File")){

            ImGui::MenuItem("Open", NULL, &fe_open);

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("History")){

            for(const auto &tab: tabs){
                if(!tab.second->opened){
                    ImGui::MenuItem(tab.second->GetName().c_str(), NULL, &tab.second->opened);
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;

    // Passing a bool* to BeginTabItem() is similar to passing one to Begin():
    // the underlying bool will be set to false when the tab is closed.

    if(!tabs.empty()) {
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
            for (const auto &tab: tabs) {
                tab.second->Render();
            }
            ImGui::EndTabBar();
        }
        ImGui::Separator();
    }
//    }else{
//        fe_open = true;
//    }

    if(fe_open){
        FileExplorer();
    }

    ImGui::End();
}