//
// Created by Brandon Boudreaux on 3/16/23.
//

#ifndef GRAPHICS_TRIANGLE_H
#define GRAPHICS_TRIANGLE_H

#include "RenderObject.h"
#include "imgui.h"

namespace PhyG {
    class Triangle : public PhyG::RenderObject {
    public:
        Triangle(std::string vertex_shader_location, std::string fragment_shader_location);
        ~Triangle();
        void Render();
        void RenderMenus();

    private:
        bool open = true;

        const GLfloat vertices[18] = {
                // Verticies                        // Color Values
                0.0f,  0.5f,  0.0f, 1.0, 0.0, 0.0,
                0.5f, -0.5f,  0.0f, 0.0, 1.0, 0.0,
                -0.5f, -0.5f,  0.0f, 0.0, 0.0, 1.0
        };

        // Arrays to manipulate the colors
        GLfloat col1[3] = {
                vertices[3], vertices[4], vertices[5]
        };
        GLfloat col2[3] = {
                vertices[9], vertices[10], vertices[11]
        };
        GLfloat col3[3] = {
                vertices[15], vertices[16], vertices[17]
        };
    };
}

#endif //GRAPHICS_TRIANGLE_H
