#include "World/World.h"
#include "World/CameraController.h"

Window window = Window(1280,720, "Examples - Cube");

Camera camera = Camera(&window, glm::vec3{0, 0, 8});
CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Object* cube;
Shader shader;

void loop(){
  glClearColor(255,255,255,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  controller.Update();
  
  world.Render();
  world.Draw();
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

#include "attributes.cpp"

int main(){
  shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
  
  Buffer* cube_positions = new Buffer({{ShaderType::Float3, "a_position"}});
  cube_positions->SetData((float*)cube_vertices_, sizeof(cube_vertices_));
  Buffer* cube_colors = new Buffer({{ShaderType::Float3, "a_color"}});
  cube_colors->SetData((float*)cube_colors_, sizeof(cube_colors_));
  cube = new Object(new VertexArray({cube_positions, cube_colors}), shader);
  
  world.AddObject(cube);
  
  controller.Bind(&camera);
  window.Start(loop);
}