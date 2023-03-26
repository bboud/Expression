//
// Created by Brandon Boudreaux on 3/24/23.
//

#ifndef GRAPHICS_SCENEVIEWER_H
#define GRAPHICS_SCENEVIEWER_H

#include "Window.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Cube.h"
#include "WorldQuad.h"
#include <unordered_map>

namespace PhyG{
    class SceneViewer : public Window {
    public:
        explicit SceneViewer(bool *o);
        ~SceneViewer();
        void Render() override;
        void Update() override;
    private:
        std::unique_ptr<Framebuffer> f;
        std::unique_ptr<Camera> cam;

        std::unordered_map<std::string, std::unique_ptr<RenderObject>> scene_objects;

        glm::mat4 projection;
    };
}

#endif //GRAPHICS_SCENEVIEWER_H