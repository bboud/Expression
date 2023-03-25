//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include "Object.h"
#include "glfw/glfw3.h"

namespace PhyG{
    class Camera : public Object {
    public:
        Camera();
        Camera(glm::vec3 pos);
        // Maybe another constructor for initial lookat? Who knows..

        ~Camera();
        void Update(GLFWwindow * w);

        void SetLookAt(glm::vec3 t);
        glm::vec3 GetLookAt();

        glm::vec3 GetForward();
        glm::vec3 GetUp();

        glm::mat4 GetView(){
            return glm::lookAt(
                    GetPos(),
                    GetLookAt(),
                    GetUp()
                    );
        }

    private:
        glm::vec3 target = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 direction;
        glm::vec3 up;
        glm::vec3 forward;
    };
}

#endif //GRAPHICS_CAMERA_H
