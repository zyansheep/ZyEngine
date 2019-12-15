cmake_minimum_required (VERSION 3.10)
project(OpenGLPlay)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Unix Makefiles")


option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_INSTALL OFF)

#GLFW
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

#OpenGL Loader
include_directories(libs/glad/include)

#OpenGL Math Library
include_directories(libs/glm)

#Dear ImGui
include_directories(libs/imgui)

include_directories(src)

#Find Sources and Headers in src folder
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

#add those files to a list
source_group (TREE ${CMAKE_SOURCE_DIR}/src PREFIX "" FILES ${SOURCES} ${HEADERS})

set (IMGUI_SRC
libs/imgui/imgui.cpp
libs/imgui/imgui_draw.cpp
libs/imgui/imgui_demo.cpp
libs/imgui/imgui_widgets.cpp
libs/imgui/examples/imgui_impl_opengl3.cpp
libs/imgui/examples/imgui_impl_glfw.cpp)

#define executable
add_executable (OpenGLPlay ${SOURCES} ${HEADERS} libs/glad/src/glad.c ${IMGUI_SRC})
target_link_libraries (OpenGLPlay glfw)

execute_process(COMMAND "./build/OpenGLPlay"
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


