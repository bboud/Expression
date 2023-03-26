//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_WORLDQUAD_H
#define GRAPHICS_WORLDQUAD_H

#include "RenderObject.h"

namespace PhyG {

    class WorldQuad : public RenderObject {
    public:
        WorldQuad();
        ~WorldQuad();
    private:
        GLfloat vertices[12] = {
                // Position
                -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,
        };
    };

} // PhyG

#endif //GRAPHICS_WORLDQUAD_H
