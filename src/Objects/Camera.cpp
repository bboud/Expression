//
// Created by Brandon Boudreaux on 3/25/23.
//

#include "Camera.h"

namespace Expression{
    Camera::Camera() {
        SetName("Camera");

        // This must be called first otherwise the update function will not have initialized values
        SetLookAt(glm::vec3(0.0, 0.0, 0.0));
    }

    Camera::Camera(glm::vec3 pos) {
        SetName("Camera");
        SetPos(pos);

        // This must be called first otherwise the update function will not have initialized values
        SetLookAt(glm::vec3(0.0, 0.0, 0.0));
    }

    Camera::~Camera() {}

    // Run on update loop
    void Camera::Update() {
        // Recalculate forward
        glm::vec3 tup = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 right = glm::normalize(glm::cross(tup, GetForward()));

        up = glm::normalize(glm::cross(GetForward(), right));
    }

    void Camera::SetLookAt(glm::vec3 t) {
        target = t;
        forward = glm::normalize(GetPos()-target);
    }

    glm::vec3 Camera::GetLookAt() {
        return target;
    }

    glm::vec3 Camera::GetForward() {
        return forward;
    }

    glm::vec3 Camera::GetUp() {
        return up;
    }
}