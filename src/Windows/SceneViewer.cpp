//
// Created by Brandon Boudreaux on 3/24/23.
//

#include "SceneViewer.h"

namespace PhyG{
    SceneViewer::SceneViewer() {
        f = std::make_unique<Framebuffer>(ImVec2(800,600));

        cam = std::make_unique<Camera>();
        cam->SetPos(glm::vec3(3,3,3));
        cam->SetLookAt(glm::vec3(0,0,0));

        cube = std::make_unique<Cube>("../shaders/cube.vert", "../shaders/cube.frag",
                                      glm::vec3(0.0, 0.0, -3.0), glm::vec3());
        title = "Scene Viewer";
    }

    SceneViewer::~SceneViewer() {}

    void SceneViewer::Update(GLFWwindow *w) {
        cam->Update(w);
    }

    void SceneViewer::Render() {
        if(!open){
            return;
        }

        ImVec2 nowSize = f->GetSize();

        f->BindFBO();
        glViewport(0,0, nowSize.x, nowSize.y);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube->BindTextures();
        cube->BindShader();

        // Default Camera
        glm::mat4 model = glm::translate(glm::mat4(1.0), cube->GetPos());
        projection = glm::perspective(glm::radians(45.0f),
                                      (float)f->GetSize().x/(float)f->GetSize().y,
                                      0.1f, 100.0f);

        glm::mat4 view = cam->GetView();

        cube->SetCameraUniforms(model, view, projection);
        cube->BindVAO();

        cube->Draw();

        cube->UnbindVAO();

        f->UnBindFBO();

        ImGui::Begin(title, &open);
        {
            ImGui::BeginChild(title);

            ImVec2 newSize = ImGui::GetContentRegionAvail();

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