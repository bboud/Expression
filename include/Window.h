//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include "imgui.h"
#include "lua.hpp"

namespace PhyG{
    class Window {
    public:
        explicit Window(bool *o);
        ~Window();

        virtual void Render();
        virtual void Update();
        bool GetOpen();
    protected:
        bool* open;
        ImVec2 size;
        const char * name = "Untitled Window";
    };
};

#endif //GRAPHICS_WINDOW_H
