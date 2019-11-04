#include <iostream>
#include "Window.cpp"
#include "Shader.cpp"

Window window = Window(600,600, "Neural Molecular Dynamics");
void setup(){
  //Triangle vertex positions
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  float positions[6] = {
    -0.5f, -0.5f,
    0.0f, 0.5f,
    0.5f, -0.5f
  };
  
  //Create vertex buffer
  unsigned int buffer;
  glGenBuffers(1, &buffer); //Generate new buffer
  printGlError("GenBuffers");
  glBindBuffer(GL_ARRAY_BUFFER, buffer); //Specify kind of buffer
  printGlError("BindBuffers");
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); //Put information into buffer
  printGlError("BufferData");
  
  glEnableVertexAttribArray(0);
  printGlError("VertexAttrib");
  
  //adress of vertex array, size of each vertex, type value, is it normalized?, stride,             offset
  glVertexAttribPointer(0, 2,                     GL_FLOAT, GL_FALSE,           sizeof(float) * 2, (const void*)0);
  printGlError("VertexAttribPointer");
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  printGlError("BindBuffer");
  
  Shader triangleShader = Shader(
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
  triangleShader.use();
  
  glClearColor(0.5,0.5,1.0,1.0);
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT);
  //printGlError("glClear");
  
  glDrawArrays(GL_TRIANGLES, 0, 3);
  //printGlError("glDrawArrays");
}

int main(void){
  setup();
  window.start(loop);
}
