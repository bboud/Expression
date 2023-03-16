#ifndef PHY_GRAPHICS_RENDEROBJECT_H
#define PHY_GRAPHICS_RENDEROBJECT_H

/*
 * PhyG::RenderObject abstracts away some usual calls to openGL that have to happen for every basic object.
 */

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "macros.h"

namespace PhyG{
    class RenderObject {
    protected:
        RenderObject(std::string vertex_shader_location, std::string fragment_shader_location);
        // Render object should have a base shader just in case one was not provided for some reason..
        RenderObject();

        ~RenderObject();

    public:
        void Render();
        // Place inline simple bind/unbind calls.
        inline void UnbindVAO() { glBindVertexArray(0); }
        inline void UnbindVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        inline void UnbindEBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        inline void BindVAO() { glBindVertexArray(vao); }
        inline void BindVBO() { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
        inline void BindEBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); }

    private:
        Shader *s;
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
    };
}

#endif //PHY_GRAPHICS_RENDEROBJECT_H
