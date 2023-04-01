#include "Application.h"

 namespace Expression{
     void Application::glfw_error_callback(int error, const char *description) {
         std::cerr << "GLFW Error: " << error << ": " << description << std::endl;
     }

     Application::Application() {
         glfwSetErrorCallback(glfw_error_callback);
         if (!glfwInit()) {
             //fprintf(stderr, "GLFW was unable to initalize...");
             std::cerr << "GLFW Error: GLFW was unable to initialize.. " <<  std::endl;
             return;
         }

#ifdef __APPLE__
         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#endif
         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

         app_state.window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_NAME, NULL, NULL);
         if (app_state.window == NULL){
             std::cerr << "We couldn't create the window!" <<  std::endl;
             return;
         }

         glfwMakeContextCurrent(app_state.window);
         glfwSwapInterval(1);

         // Initialize after creating window
         int v = gladLoadGL();
         if(v == 0){
             std::cerr << "There was a problem initializing GL through glad!" << std::endl;
         }

         // ### IMGUI ###
         IMGUI_CHECKVERSION();
         ImGui::CreateContext();
         ImGuiIO &io = ImGui::GetIO(); (void)io;

         ImGui::StyleColorsDark();

         ImGui_ImplGlfw_InitForOpenGL(app_state.window, true);
         ImGui_ImplOpenGL3_Init(GLSL_VERSION);
         //#############

         // Opening Lua
         app_state.L = luaL_newstate();
         luaL_openlibs(app_state.L);
     }

     Application::~Application() {
         lua_close(app_state.L);

         // ### IMGUI ###
         ImGui_ImplOpenGL3_Shutdown();
         ImGui_ImplGlfw_Shutdown();
         ImGui::DestroyContext();
         //#############

         glfwDestroyWindow(app_state.window);
         glfwTerminate();
     }

     void Application::run() {
         while(!glfwWindowShouldClose(app_state.window)){

             //### IMGUI ###
             ImGui_ImplOpenGL3_NewFrame();
             ImGui_ImplGlfw_NewFrame();

             ImGui::NewFrame();

             static bool show_demo = false;
             static bool show_console = false;
             static bool show_scene_view = false;

             if(ImGui::BeginMainMenuBar()){
                 if(ImGui::BeginMenu("Graphics")){
                     ImGui::MenuItem("Demo Menu", nullptr, &show_demo);
                     if(ImGui::MenuItem("Console", nullptr, &show_console)){
                        if(show_console){
                            app_state.windows.push_back(std::make_unique<Console>(&show_console));
                        }
                     }
                     if(ImGui::MenuItem("Scene View", nullptr, &show_scene_view)){
                         if(show_scene_view){
                             app_state.windows.push_back(std::make_unique<SceneViewer>(&show_scene_view));
                         }
                     }
                     ImGui::EndMenu();
                 }
                 ImGui::EndMainMenuBar();
             }

             for(auto w = app_state.windows.begin(); w != app_state.windows.end();){
                if(w->get()->GetOpen()){
                    w->get()->Render();
                    w->get()->Update();
                    w++;
                }else{
                    w = app_state.windows.erase(w);
                }
             }

             if(show_demo){
                 ImGui::ShowDemoWindow(&show_demo);
             }

             ImGui::Render();
             //#############

             // Adjust the viewport for window resizing
             int display_w, display_h;
             glfwGetFramebufferSize(app_state.window, &display_w, &display_h);
             glViewport(0, 0, display_w, display_h);
             glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
             glClear(GL_COLOR_BUFFER_BIT);

             // Render for IMGUI
             ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

             glfwPollEvents();
             glfwSwapBuffers(app_state.window);
         }
     }
}
