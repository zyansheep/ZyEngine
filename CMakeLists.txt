cmake_minimum_required (VERSION 3.10)
project(ZyEngine)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Unix Makefiles")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLAD")

option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_INSTALL OFF)

#GLFW
add_subdirectory(libs/glfw)

#OpenGL Loader
include_directories(libs/glad/include)
add_subdirectory(libs/glad)

#OpenGL Math Library
add_subdirectory(libs/glm)


#Dear ImGui
include_directories(libs/imgui)

include_directories(src)

#Find Sources and Headers in src folder
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

#add those files to a list
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "" FILES ${SOURCES} ${HEADERS})

set (IMGUI_SRC
libs/imgui/imgui.cpp
libs/imgui/imgui_draw.cpp
libs/imgui/imgui_demo.cpp
libs/imgui/imgui_widgets.cpp
libs/imgui/examples/imgui_impl_opengl3.cpp
libs/imgui/examples/imgui_impl_glfw.cpp)

add_library(ZyEngine STATIC ${SOURCES} ${HEADERS} ${IMGUI_SRC})
target_link_libraries(ZyEngine glfw)
target_link_libraries(ZyEngine glm)
target_link_libraries(ZyEngine glad)

add_subdirectory(test)

add_subdirectory(examples)
