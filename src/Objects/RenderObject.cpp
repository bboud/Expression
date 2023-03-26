//
// Created by Brandon Boudreaux on 3/25/23.
//

#include "RenderObject.h"

namespace PhyG {
    void RenderObject::SetCameraUniforms(glm::mat4 v, glm::mat4 p) {
        model = glm::translate(glm::mat4(1.0), GetPos());
        model = glm::translate(model, GetScale());

        // Is this the best way to do this?
        model = glm::rotate(model, GetRot().x, glm::vec3(1.0, 0.0, 0.0));
        model = glm::rotate(model, GetRot().y, glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, GetRot().z, glm::vec3(0.0, 0.0, 1.0));

        shader->SetCameraUniforms(model, v, p);
    }

    RenderObject::RenderObject() {}

    RenderObject::~RenderObject(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void RenderObject::Draw() {
        glDrawArrays(GL_TRIANGLES, 0, vertCount);
    }
} // PhyG