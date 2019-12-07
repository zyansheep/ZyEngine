#include <iostream>
#include <vector>
#include <array>
#include <math.h>

#include "Core/World.cpp"
#include "Core/CameraController.h"

//unsigned int shader;
//unsigned int tri_vao;

//float ScaleCount = 1.0f;
//Vertex<float, 2> transition = {0.0f, 0.0f};
//unsigned int main_uniform_scale;
//unsigned int main_uniform_transition;

Window window = Window(600,600, "Graphics Engine Testing");
Camera camera = Camera(glm::vec3{4,4,3});
CameraController controller = CameraController(&camera, &window);
World world = World(&window, &camera);

Object triangle;
Object cube;
Shader shader;

#include "cube.cpp"
void setup(){
  //controller.Bind(&camera);
  //Triangle vertex positions
  shader = Shader("../src/shaders/main.vert", "../src/shaders/main.frag");
  
  Buffer* cube_positions = new Buffer({{ShaderType::Float3, "a_position"}});
  cube_positions->SetData((float*)cube_vertices_, sizeof(cube_vertices_));
  Buffer* cube_colors = new Buffer({{ShaderType::Float3, "a_color"}});
  cube_colors->SetData((float*)cube_colors_, sizeof(cube_colors_));
  
  cube = Object(new VertexArray({cube_positions, cube_colors}), &shader);
  world.addObject(&cube);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.5,0.5,1.0,1.0);
  
  world.render();
}

void loop(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  controller.Update();
  world.render();
  world.draw();
}

int main(void){
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.start(loop);
}
