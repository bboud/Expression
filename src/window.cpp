#include "window.h"

 void Window::glfw_error_callback(int error, const char *description) {
    std::cerr << "GLFW Error: " << error << ": " << description << std::endl;
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){

}

Window::Window() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        //fprintf(stderr, "GLFW was unable to initalize...");
        std::cerr << "GLFW Error: GLFW was unable to initialize.. " <<  std::endl;
        return;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#endif

    window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_NAME, NULL, NULL);
    if (window == NULL){
        std::cerr << "We couldn't create the window!" <<  std::endl;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);

    // Initialize after creating window
    int v = gladLoadGL();
    if(v == 0){
        std::cerr << "There was a problem initializing GL through glad!" << std::endl;
    }

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

    // Opening Lua
    L = luaL_newstate();
    luaL_openlibs(L);
}

Window::~Window() {
    lua_close(L);

    // ### IMGUI ###
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    //#############

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::run() {
    editor = std::make_unique<PhyG::Editor>(L);
    s = std::make_unique<PhyG::SceneViewer>();

    while(!glfwWindowShouldClose(window)){

        //### IMGUI ###
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        if(ImGui::BeginMainMenuBar()){
            if(ImGui::BeginMenu("Graphics")){
                ImGui::MenuItem("Demo Menu", NULL, &show_demo);
                ImGui::MenuItem("Editor", NULL, &editor->open);
                ImGui::MenuItem("Scene Viewer", NULL, &show_sv);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if(show_demo){
            ImGui::ShowDemoWindow(&show_demo);
        }
        if(editor->open){
            editor->Render();
        }

        if(show_sv){
            s->Render();
        }

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

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}