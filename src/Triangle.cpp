//
// Created by Brandon Boudreaux on 3/16/23.
//

#include "include/Triangle.h"

PhyG::Triangle::Triangle(std::string vertex_shader_location, std::string fragment_shader_location) : PhyG::RenderObject(vertex_shader_location, fragment_shader_location){
    // We don't need the EBO for this..
    UnbindEBO();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*)0);
    // GLuint index
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    UnbindVAO();
    UnbindVBO();
    UnbindEBO();
}

PhyG::Triangle::~Triangle() {}

void PhyG::Triangle::RenderMenus() {
    if(!open){
        return;
    }
    if(ImGui::Begin("Triangle", &open)){

        ImGui::ColorEdit3("Vert 1", col1);
        ImGui::ColorEdit3("Vert 2", col2);
        ImGui::ColorEdit3("Vert 3", col3);

        BindVBO();
        glBufferSubData(GL_ARRAY_BUFFER, 3*sizeof(GLfloat), sizeof(col1), col1);
        glBufferSubData(GL_ARRAY_BUFFER, 3*3*sizeof(GLfloat), sizeof(col2), col2);
        glBufferSubData(GL_ARRAY_BUFFER, 5*3*sizeof(GLfloat), sizeof(col3), col3);
        UnbindVBO();
    }
    ImGui::End();
}

void PhyG::Triangle::Render(){
    RenderObject::Render();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    UnbindVAO();
}