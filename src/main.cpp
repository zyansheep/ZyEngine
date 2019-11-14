#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include "glad/glad.h"

#include "Functions.cpp"
#include "Window.cpp"
#include "Shader.cpp"
#include "VertexArrayObject.cpp"

//unsigned int shader;
//unsigned int tri_vao;

float Scale = 1.0f;
unsigned int scale_uniform;

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
  scale_uniform = glGetUniformLocation(shader.program, "gScale");
  std::cout << scale_uniform << '\n';
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
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  Scale += 0.01f;
  
  glUniform1f(scale_uniform, sinf(Scale));
  triangle->draw();
  square->draw();
}

int main(void){
  
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.start(loop);
  
}
