//
// Created by Brandon Boudreaux on 3/24/23.
//

#ifndef GRAPHICS_TEXTURE2D_H
#define GRAPHICS_TEXTURE2D_H

#include "glad.h"
#include "stb_image.h"

namespace PhyG{
    class Texture2D {
    public:
        Texture2D(const char * path);
        ~Texture2D();

        inline void BindTex() {
            glActiveTexture(tex);
            glBindTexture(GL_TEXTURE_2D, tex);
        }
        inline void UnBindTex() {glBindTexture(GL_TEXTURE_2D, 0);}

    private:
        GLuint tex;
    };
}


#endif //GRAPHICS_TEXTURE2D_H
