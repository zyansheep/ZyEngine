cmake_minimum_required (VERSION 2.6)
project(OpenGLPlay)

option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_INSTALL OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/glad/include)

#Recursively find all source files in src dir
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.h)


#add those files to a list
source_group (TREE ${CMAKE_SOURCE_DIR}/src PREFIX "" FILES ${SOURCES} ${HEADERS})

#define executable
add_executable (OpenGLPlay ${SOURCES} ${HEADERS} ${CMAKE_SOURCE_DIR}/glad/src/glad.c)
target_link_libraries (OpenGLPlay glfw)
