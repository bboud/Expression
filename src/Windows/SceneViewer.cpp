//
// Created by Brandon Boudreaux on 3/24/23.
//

#include "SceneViewer.h"

namespace PhyG{
    SceneViewer::SceneViewer(bool *o) : Window(o) {
        f = std::make_unique<Framebuffer>(ImVec2(500,500));

        cam = std::make_unique<Camera>();
        cam->SetPos(glm::vec3(4, 4, 4));
        cam->SetLookAt(glm::vec3(0,0,0));

        scene_objects.insert({"Cube 1", std::make_unique<Cube>("../shaders/cube.vert", "../shaders/cube.frag")});
        //scene_objects.insert({"World Plane", std::make_unique<WorldQuad>()});

        name = "Scene Viewer";
    }

    SceneViewer::~SceneViewer() {}

    void SceneViewer::Update() {
        cam->Update();
        scene_objects.find("Cube 1")->second->SetRot(glm::vec3(glm::cos(glfwGetTime()), glm::sin(glfwGetTime()), 1.0));
        //scene_objects.find("World Plane")->second->SetRot(glm::vec3(glm::cos(glfwGetTime()), glm::sin(glfwGetTime()), 1.0));
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

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)f->GetSize().x/(float)f->GetSize().y,
                                                0.1f, 100.0f);

        for(auto &robj : scene_objects){
            robj.second->BindTextures();
            robj.second->BindShader();
            robj.second->SetCameraUniforms(cam->GetView(), projection);
            robj.second->BindVAO();
            robj.second->Draw();
            robj.second->UnbindVAO();
        }

        f->UnBindFBO();

        ImGui::Begin(name, open);
        {
            ImGui::BeginChild(name);

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