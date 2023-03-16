#include "window.h"

static void glfw_error_callback(int error, const char *description) {
    //fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    // Use STD instead.
    std::cerr << "GLFW Error: " << error << ": " << description << std::endl;
}

Window::Window() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "GLFW was unable to initalize...");
        std::cerr << "GLFW Error: GLFW was unable to initialize.. " <<  std::endl;
        return;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_NAME, NULL, NULL);
    if (window == NULL){
        fprintf(stderr, "We couldn't create the window!");
        return;
    }

    // Initialie after creating window
    glewInit();

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // ### IMGUI ###
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

#ifdef DARK_COLORS
    ImGui::StyleColorsDark();
#elif
    ImGui::StyleColorsClassic();
#endif

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    //#############
}
Window::~Window() {
    // ### IMGUI ###
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    //#############

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::run() {
    while(!glfwWindowShouldClose(window)){

        //### IMGUI ###
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        if(ImGui::BeginMainMenuBar()){
            if(ImGui::BeginMenu("Graphics")){
                ImGui::MenuItem("Settings", NULL, &show_settings);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (show_settings){
            PhyG::Menu::Settings(&show_settings, &clear_color);
        }

        // Views should be called here

        //////

        ImGui::Render();
        //#############

        // Adjust the viewport for window resizing
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render for IMGUI
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Graphics Render Loop here

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}