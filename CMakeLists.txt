cmake_minimum_required(VERSION 3.23)
project(graphics)

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

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_glfw.cpp)

add_executable(phy_graphics ${SOURCES})

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/imgui)

# You should also build these yourself first :>
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/glfw)
set(LUA_DIR ${PROJECT_SOURCE_DIR}/lua)

target_link_directories(phy_graphics PRIVATE ${GLFW_DIR}/build/src)
target_link_directories(phy_graphics PRIVATE ${LUA_DIR}/src)

target_include_directories(phy_graphics PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_include_directories(phy_graphics PRIVATE ${IMGUI_DIR}/backends)
target_include_directories(phy_graphics PRIVATE ${IMGUI_DIR})

target_include_directories(phy_graphics PRIVATE ${GLFW_DIR}/include)

target_include_directories(phy_graphics PRIVATE ${LUA_DIR}/src)

target_include_directories(phy_graphics PRIVATE ${PROJECT_SOURCE_DIR}/glm)

target_link_libraries(phy_graphics PRIVATE glfw3)
target_link_libraries(phy_graphics PRIVATE lua)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(phy_graphics PRIVATE GL X11 Xrandr Xinerama Xi Xcursor pthread dl)
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(phy_graphics PRIVATE "-framework OpenGL -framework Cocoa -framework IOkit")
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(phy_graphics PRIVATE opengl32)
else ()
    message(WARNING "Unsupported system: ${CMAKE_HOST_SYSTEM_NAME}")
endif ()
