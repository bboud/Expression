//
// Created by Brandon Boudreaux on 3/25/23.
//

#include "WorldQuad.h"

namespace PhyG {
    WorldQuad::WorldQuad() {
        SetPos(glm::vec3(0.0, 0.0, 0.0));
        //SetRot();
        SetScale(glm::vec3(1.0, 1.0, 1.0));

        SetName("World Plane");

        // Create the shader
        shader = std::make_unique<Shader>("../shaders/world_quad.vert", "../shaders/world_quad.vert");
        tex = std::make_unique<Texture2D>("../resources/bricks2.jpg");

        vertCount = 4;

        glGenVertexArrays(1, &VAO);
        BindVAO();

        glGenBuffers(1, &VBO);
        BindVBO();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void *)0);
        // GLuint index
        glEnableVertexAttribArray(0);

        UnbindVAO();
        UnbindVBO();
    }

    WorldQuad::~WorldQuad() {}
} // PhyG