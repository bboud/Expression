//
// Created by Brandon Boudreaux on 3/24/23.
//

#include "SceneViewer.h"

namespace PhyG{
    SceneViewer::SceneViewer() {
        t = std::make_unique<PhyG::Triangle>("../shaders/base.vert", "../shaders/base.frag");
        f = std::make_unique<Framebuffer>(ImVec2(500,500));
    }

    SceneViewer::~SceneViewer() {

    }

    void SceneViewer::Render() {
        f->BindFBO();
        glViewport(0,0, f->GetSize().x, f->GetSize().y);
        t->Render();
        f->UnBindFBO();

        ImGui::Begin("Scene View");
        {
            ImGui::BeginChild("Scene View");

            ImVec2 newSize = ImGui::GetContentRegionAvail();
            ImVec2 nowSize = f->GetSize();

            if (newSize.x != nowSize.x || newSize.y != nowSize.y ){
                f->SetSize(newSize);
            }
            ImGui::Image(
                    (ImTextureID)f->GetTexture(),
                    ImGui::GetContentRegionAvail(),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
            );
        }
        ImGui::EndChild();
        ImGui::End();

    }
}