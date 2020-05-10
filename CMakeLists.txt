cmake_minimum_required (VERSION 3.17)
project(ZyEngine)

#Options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR "Ninja")

#Dependencies
add_subdirectory(libs/glad)
add_subdirectory(libs/glfw)
add_definitions(-DGLFW_INCLUDE_NONE)
add_subdirectory(libs/glm)

#Find Sources and Headers in src folder
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
include_directories(src)

#Imgui sources
set (IMGUI_SRC
libs/imgui/imgui.cpp
libs/imgui/imgui_draw.cpp
libs/imgui/imgui_demo.cpp
libs/imgui/imgui_widgets.cpp
libs/imgui/examples/imgui_impl_opengl3.cpp
libs/imgui/examples/imgui_impl_glfw.cpp)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library(ZyEngine ${SOURCES} ${HEADERS} ${IMGUI_SRC})
target_include_directories(ZyEngine PUBLIC libs/imgui libs/stb)
target_link_libraries(ZyEngine LINK_PUBLIC glad glfw glm)

add_subdirectory(test)

add_subdirectory(examples)
