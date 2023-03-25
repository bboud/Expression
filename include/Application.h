#ifndef PHY_GRAPHICS_WINDOW_H
#define PHY_GRAPHICS_WINDOW_H

#include "config.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include "Editor.h"
#include <memory>
#include <vector>
#include "lua.hpp"
#include "SceneViewer.h"

namespace PhyG{
    class Application{
    public:
        Application();
        ~Application();
        void run();
    private:
        GLFWwindow *window;

        std::unique_ptr<PhyG::Editor> editor;

        static void glfw_error_callback(int error, const char *description);
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

        lua_State * L;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        bool show_demo = false;
        bool show_sv = true;
        std::unique_ptr<PhyG::SceneViewer> s;
    };
}

#endif