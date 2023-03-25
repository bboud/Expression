//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include "imgui.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include <memory>

namespace PhyG{
    class Window {
    public:
        bool opened = false;
    protected:
        ImVec2 size;
        const char * title;
    };
};

#endif //GRAPHICS_WINDOW_H
