//
// Created by Brandon Boudreaux on 3/24/23.
//

#ifndef GRAPHICS_FRAMEBUFFER_H
#define GRAPHICS_FRAMEBUFFER_H

#include "glad.h"
#include <iostream>
#include "imgui.h"

namespace Expression{
    class Framebuffer {
    public:
        Framebuffer(ImVec2 s);
        ~Framebuffer();

        inline void BindFBO(){glBindFramebuffer(GL_FRAMEBUFFER, fbo);}
        inline void UnBindFBO(){glBindFramebuffer(GL_FRAMEBUFFER, 0);}
        inline void BindTex() {glBindTexture(GL_TEXTURE_2D, tex);}
        inline void UnBindTex() {glBindTexture(GL_TEXTURE_2D, 0);}
        inline void BindRBO() {glBindRenderbuffer(GL_RENDERBUFFER, rbo);}
        inline void UnBindRBO() {glBindRenderbuffer(GL_RENDERBUFFER, 0);}

        void SetSize(ImVec2 size);
        ImVec2 GetSize();

        GLuint GetTexture();

    private:
        GLuint fbo;
        GLuint tex;
        GLuint rbo;

        ImVec2 size;
    };
}

#endif //GRAPHICS_FRAMEBUFFER_H
