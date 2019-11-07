#include <iostream>
#include <vector>
#include <array>
#include "glad/glad.h"

#include "Functions.cpp"
#include "Window.cpp"
#include "Shader.cpp"
#include "ShaderFromFile.cpp"
#include "VertexArrayObject.cpp"

//unsigned int shader;
//unsigned int tri_vao;

Window window = Window(600,600, "Neural Molecular Dynamics");
VertexArrayObject<2> *triangle;
VertexArrayObject<1> *square;
unsigned int shader;
void setup(){
  //Triangle vertex positions
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
  shader = LoadShaders("../src/shaders/main.vert", "../src/shaders/main.frag");
  triangle->setShader(shader);
  
  
  glClearColor(0.5,0.5,1.0,1.0);
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  triangle->draw();
}

int main(void){
  
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.start(loop);
  
}
