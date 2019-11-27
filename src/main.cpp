#include <iostream>
#include <vector>
#include <array>
#include <math.h>

#include "Core/World.cpp"

//unsigned int shader;
//unsigned int tri_vao;

//float ScaleCount = 1.0f;
//Vertex<float, 2> transition = {0.0f, 0.0f};
//unsigned int main_uniform_scale;
//unsigned int main_uniform_transition;

Window window = Window(600,600, "Graphics Engine Testing");
Camera camera = Camera(45.0f, &window, glm::vec3(4,3,3));
World world = World(&window, &camera);

Object triangle;
Shader shader;
void setup(){
  //Triangle vertex positions
  shader = Shader("../src/shaders/main.vert", "../src/shaders/main.frag");
  
  VertexArray* triangleVAO = new VertexArray({
    new VertexBuffer({
      {-0.5f, -0.5f, 0.0f},
      { 0.0f,  0.5f, 0.0f},
      { 0.5f, -0.5f, 0.0f}
    }),
    new VertexBuffer({
      { 1.0f,  0.0f, 0.0f},
      { 0.0f,  1.0f, 0.0f},
      { 0.0f,  0.0f, 1.0f}
    }),
  });
  triangle = Object(triangleVAO, &shader);
  world.addObject(&triangle);
  
  glClearColor(0.5,0.5,1.0,1.0);
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  world.render();
  world.draw();
  //square->draw();
}

int main(void){
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.start(loop);
}
