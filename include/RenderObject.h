//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_RENDEROBJECT_H
#define GRAPHICS_RENDEROBJECT_H

#include "Object.h"
#include "glad.h"
#include "Texture2D.h"
#include "Shader.h"

namespace PhyG {

    class RenderObject : public Object{
    public:
        RenderObject();
        ~RenderObject();

        inline void BindVAO(){ glBindVertexArray(VAO); }
        inline void BindVBO(){ glBindBuffer(GL_ARRAY_BUFFER, VBO); }
        inline void UnbindVAO(){ glBindVertexArray(0); }
        inline void UnbindVBO(){ glBindBuffer(GL_ARRAY_BUFFER, 0); }
        inline void BindShader() { shader->Use(); }
        inline void BindTextures() { tex->BindTex(); }

        void SetCameraUniforms(glm::mat4 v, glm::mat4 p);
        void Draw();

    protected:
        std::unique_ptr<Texture2D> tex;
        std::unique_ptr<Shader> shader;

        glm::mat4 model = glm::mat4(1.0);

        bool open = true;
        GLuint VAO, VBO;
        int vertCount;
    };

} // PhyG

#endif //GRAPHICS_RENDEROBJECT_H
