cmake_minimum_required (VERSION 2.6)
project(OpenGLPlay)

set (CMAKE_CXX_STANDARD 11)

option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_INSTALL OFF)
add_subdirectory(glfw)

include_directories(glfw/include)
include_directories(glad/include)

#Recursively find all source files in src dir
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

#add those files to a list
source_group (TREE src PREFIX "" FILES ${SOURCES} ${HEADERS})

#define executable
add_executable (OpenGLPlay ${SOURCES} ${HEADERS} glad/src/glad.c)
target_link_libraries (OpenGLPlay glfw)
