//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace PhyG{
    class Object {
    public:
        void SetPos(glm::vec3 pos);
        glm::vec3 GetPos();

        void SetScale(glm::vec3 s);
        glm::vec3 GetScale();

        void SetRot(glm::vec3 rot);

        glm::vec3  GetRot();
        void SetName(const char* n);

        const char* GetName();
    protected:
        glm::vec3 position = glm::vec3(0.0);
        glm::vec3 scale = glm::vec3(1.0);
        glm::vec3 rotation = glm::vec3(1.0);
        const char * name = "Untitled Object";
    };
}

#endif //GRAPHICS_OBJECT_H
