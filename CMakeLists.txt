cmake_minimum_required(VERSION 3.23)
project(expression)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdeprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated-declarations")

set(SOURCES
        src/main.cpp
        src/Application.cpp

        src/Shader.cpp
        src/Texture2D.cpp
        src/Framebuffer.cpp

        src/Objects/Object.cpp
        src/Objects/RenderObject.cpp
        src/Objects/Cube.cpp
        src/Objects/Camera.cpp
        src/Objects/WorldQuad.cpp

        src/Window.cpp
        src/Windows/Editor.cpp
        src/Windows/SceneViewer.cpp
        src/Windows/SceneObjects.cpp
        src/Windows/Window.cpp
        src/Windows/Console.cpp

        src/glad.c
        src/stb_image.cpp

        src/imgui/imgui.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_demo.cpp
        src/imgui/backends/imgui_impl_opengl3.cpp
        src/imgui/backends/imgui_impl_glfw.cpp)

add_executable(expression ${SOURCES})

target_include_directories(expression PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_directories(expression PRIVATE ${PROJECT_SOURCE_DIR}/libs)

target_link_libraries(expression PRIVATE glfw3)
target_link_libraries(expression PRIVATE lua)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(expression PRIVATE GL X11 Xrandr Xinerama Xi Xcursor pthread dl)
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(expression PRIVATE "-framework OpenGL -framework Cocoa -framework IOkit")
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(expression PRIVATE opengl32)
else ()
    message(WARNING "Unsupported system: ${CMAKE_HOST_SYSTEM_NAME}")
endif ()
