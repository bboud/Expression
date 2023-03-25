//
// Created by Brandon Boudreaux on 3/21/23.
//

#ifndef GRAPHICS_TAB_H
#define GRAPHICS_TAB_H

#include "imgui.h"

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "lua.hpp"

namespace PhyG {
    class Tab {
    public:
        Tab(std::filesystem::path p, lua_State * L);
        ~Tab();
        void Render();
        bool opened = true;
        std::string GetName();
    private:
        void LoadTextIn();
        std::filesystem::path path;

        char * buffer;
        unsigned int buffer_size = 512000;
        lua_State * lua;

        std::string tab_title;
        const ImGuiInputTextFlags text_edit_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AllowTabInput
                | ImGuiInputTextFlags_CallbackEdit;
    };
} // PhyG

#endif //GRAPHICS_TAB_H