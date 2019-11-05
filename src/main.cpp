#include <iostream>
#include "Window.cpp"
#include "Shader.cpp"
#include "ShaderFromFile.cpp"
#include "glad/glad.h"


void setup(){
  //Triangle vertex positions
  
  float positions[6] = {
    -0.5f, -0.5f,
    0.0f, 0.5f,
    0.5f, -0.5f
  };
  
  
  //Have to do this for some reason? https://www.youtube.com/watch?v=71BLZwRGUJE&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=7
  //Create array buffer (3 lines)
  GLuint vertexArrayID; 
  glGenVertexArrays(1, &vertexArrayID);
  glBindVertexArray(vertexArrayID);
  
  unsigned int buffer;
  glGenBuffers(1, &buffer); //Generate new buffer
  glBindBuffer(GL_ARRAY_BUFFER, buffer); //Specify kind of buffer
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); //Put information into buffer
  
  glEnableVertexAttribArray(0);
  //adress of vertex array, size of each vertex, type value, is it normalized?, stride,             offset
  glVertexAttribPointer(0, 2,                     GL_FLOAT, GL_FALSE,           sizeof(float) * 2, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  /*Shader triangleShader = Shader(
  R"(
  #version 330 core

  layout(location = 0) in vec4 position;

  void main(){
    gl_Position = position;
  }
  )", R"(
  #version 330 core
  layout(location = 0) out vec4 color;

  void main(){
    color = vec4(1.0, 0.0, 1.0, 1.0);
  }
  )");
  triangleShader.use();*/
  unsigned int shader = LoadShaders("../src/shaders/main.vert", "../src/shaders/main.frag");
  glUseProgram(shader);
  
  glClearColor(0.5,0.5,1.0,1.0);
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT);
  //printGlError("glClear");
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
