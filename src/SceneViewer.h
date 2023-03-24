//
// Created by Brandon Boudreaux on 3/24/23.
//

#ifndef GRAPHICS_SCENEVIEWER_H
#define GRAPHICS_SCENEVIEWER_H

#include "glad/glad.h"
#include "imgui.h"
#include "Triangle.h"
#include <memory>
#include "Framebuffer.h"

namespace PhyG{
    class SceneViewer {
    public:
        SceneViewer();
        ~SceneViewer();
        void Render();
    private:
        ImVec2 size;
        std::unique_ptr<Triangle> t;
        std::unique_ptr<Framebuffer> f;

        GLfloat quadVertices[24] = {
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
        };
    };
}

#endif //GRAPHICS_SCENEVIEWER_H
