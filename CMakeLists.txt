cmake_minimum_required (VERSION 3.17)
project(ZyEngine)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
  set(ZYENGINE_STANDALONE TRUE)
endif()

#Compile Settings
option(ZYENGINE_BUILD_EXAMPLES "Build ZyEngine example programs" ${GLFW_STANDALONE})
option(ZYENGINE_BUILD_TESTS "Build ZyEngine test programs" ${GLFW_STANDALONE})

#Options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR "Ninja")

#Dependencies
add_subdirectory(libs/glad)
add_subdirectory(libs/glfw)
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
target_include_directories(ZyEngine PRIVATE libs/stb)
target_link_libraries(ZyEngine PRIVATE glad glfw)

target_include_directories(ZyEngine PUBLIC libs/imgui)
target_link_libraries(ZyEngine LINK_PUBLIC glm)

if (ZYENGINE_BUILD_TESTS)
  add_subdirectory(test)
endif()
if (ZYENGINE_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()