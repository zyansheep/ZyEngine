#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Functions.cpp"
#include "Window.cpp"
#include "Shader.cpp"
#include "VertexArrayObject.cpp"

//unsigned int shader;
//unsigned int tri_vao;

float ScaleCount = 1.0f;
Vertex<float, 2> transition = {0.0f, 0.0f};
unsigned int main_uniform_scale;
unsigned int main_uniform_transition;

Window window = Window(600,600, "Neural Molecular Dynamics");
VertexArrayObject<2> *triangle;
VertexArrayObject<2> *square;
Shader shader;
void setup(){
  //Triangle vertex positions
  shader = Shader("../src/shaders/main.vert", "../src/shaders/main.frag");
  triangle = new VertexArrayObject<2>();
  triangle->addVBO(std::vector<Vertex<float, 2>>{
    {-0.5f, -0.5f},
    {0.0f, 0.5f},
    {0.5f, -0.5f}
  });
  triangle->addVBO(std::vector<Vertex<float,3>>{
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
  });
  triangle->setShader(shader);
  
  square = new VertexArrayObject<2>();
  square->addVBO(std::vector<Vertex<float, 2>>{
    {0.9f, 0.9f},
    {0.9f, 0.7f},
    {0.7f, 0.7f},
    {0.7f, 0.9f}
  });
  square->addVBO(std::vector<Vertex<float,3>>{
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 1.0f}
  });
  square->setShader(shader);
  
  //assert(scale_uniform != 0xFFFFFFFF);
  
  glClearColor(0.5,0.5,1.0,1.0);
  
  main_uniform_scale = shader.getUniformLocation("scale");
  main_uniform_transition = shader.getUniformLocation("transition");
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  ScaleCount += 0.01f;
  transition.data[1] = 3 * sinf(ScaleCount);
  //std::cout << transition.data[1] << '\n';
  
  shader.Uniform(main_uniform_scale, 2 * sinf(ScaleCount));
  shader.Uniform(main_uniform_transition, transition);
  
  triangle->draw();
  square->draw();
}

int main(void){
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.start(loop);
}
