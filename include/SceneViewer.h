//
// Created by Brandon Boudreaux on 3/24/23.
//

#ifndef GRAPHICS_SCENEVIEWER_H
#define GRAPHICS_SCENEVIEWER_H

#define ImTextureID void *

#include "Window.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Cube.h"

namespace PhyG{
    class SceneViewer : Window {
    public:
        SceneViewer(GLFWwindow* w);
        ~SceneViewer();
        void Render();
        void Update();
        bool open = false;
    private:
        std::unique_ptr<Framebuffer> f;
        std::unique_ptr<Camera> cam;
        std::unique_ptr<Cube> cube;

        glm::mat4 projection;
    };
}

#endif //GRAPHICS_SCENEVIEWER_H
