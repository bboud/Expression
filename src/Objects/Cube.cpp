//
// Created by Brandon Boudreaux on 3/24/23.
//

#include "Cube.h"

namespace Expression{
    Cube::Cube(std::string vertex_shader_location, std::string fragment_shader_location){
        SetName("Cube");

        // Create the shader
        shader = std::make_unique<Shader>(vertex_shader_location, fragment_shader_location);
        tex = std::make_unique<Texture2D>("../resources/bricks2.jpg");

        vertCount = 36;

        glGenVertexArrays(1, &VAO);
        BindVAO();

        glGenBuffers(1, &VBO);
        BindVBO();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void *)0);
        // GLuint index
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        UnbindVAO();
        UnbindVBO();
    }

    Cube::~Cube() {
        glDeleteBuffers(GL_ARRAY_BUFFER, &VBO);
        glDeleteVertexArrays(GL_VERTEX_ARRAY, &VAO);
    }
}
