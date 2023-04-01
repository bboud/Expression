#ifndef PHY_GRAPHICS_WINDOW_H
#define PHY_GRAPHICS_WINDOW_H

#include "config.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad.h"
#include "GLFW/glfw3.h"

#include <cstdio>
#include <memory>
#include <unordered_map>
#include <vector>
#include "lua.hpp"
#include "Windows/SceneViewer.h"
#include "Windows/Console.h"

namespace Expression{
    typedef struct{
        GLFWwindow * window;
        lua_State * L;
        std::vector<std::unique_ptr<Window>> windows;
    }App_State;

    class Application{
    public:
        Application();
        ~Application();
        void run();

        static void glfw_error_callback(int error, const char *description);

        App_State app_state;

        ImVec4 clear_color = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
    };
}

#endif