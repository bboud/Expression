//
// Created by Brandon Boudreaux on 3/25/23.
//

#include "../Window.h"

namespace Expression{
    Window::Window(bool* o){
        open = o;
    }

    Window::~Window()= default;

    void Window::Render() {
        ImGui::Begin(name, open);
        ImGui::Text("Override me!");
        ImGui::End();
    }

    void Window::Update() {}

    bool Window::GetOpen() {
        return *open;
    }
}