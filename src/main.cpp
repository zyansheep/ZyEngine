#include <iostream>
#include <vector>
#include <array>
#include "glad/glad.h"

#include "Functions.cpp"
#include "Window.cpp"
#include "Shader.cpp"
#include "ShaderFromFile.cpp"

unsigned int shader;

unsigned int tri_vao;
void setup(){
  //Triangle vertex positions
  
  std::vector<Vertex<float, 2>> tri_points = {
    {-1.0f, -1.0f},
    {1.0f, 1.0f},
    {0.5f, -0.5f}
  };
  std::vector<Vertex<float, 3>> tri_colors = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
  };
  
  registerVAO(tri_vao);
  
  unsigned int try_points_vbo;
  registerVBO(try_points_vbo, tri_vao, 0, tri_points);
  unsigned int try_colors_vbo;
  registerVBO(try_colors_vbo, tri_vao, 1, tri_colors);
  
  //Use ShaderFromFile.cpp LoadShaders function TODO: Fix other shaders
  shader = LoadShaders("../src/shaders/main.vert", "../src/shaders/main.frag");
  
  glClearColor(0.5,0.5,1.0,1.0);
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //printGlError("glClear");
  glUseProgram(shader);
  glBindVertexArray(tri_vao);
  
  glDrawArrays(GL_TRIANGLES, 0, 3);
  //printGlError("glDrawArrays");
}

int main(void){
  Window window = Window(600,600, "Neural Molecular Dynamics");
  
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.start(loop);
  
}
