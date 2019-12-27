#include "World/World.h"

#include "attributes.cpp"

Window window = Window(1280,720, "Examples - Cube");

Camera camera = Camera(&window, glm::vec3{0, 0, 8});
CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Object* cube;

void loop(){
  world.Render();
  world.Draw();
}

void main(){
  controller.Bind(&camera);
  
  Buffer* cube_positions = new Buffer({{ShaderType::Float3, "a_position"}});
  cube_positions->SetData((float*)cube_vertices_, sizeof(cube_vertices_));
  Buffer* cube_colors = new Buffer({{ShaderType::Float3, "a_color"}});
  cube_colors->SetData((float*)cube_colors_, sizeof(cube_colors_));
  cube = new Object(new VertexArray({cube_positions, cube_colors}), shader);
  
  world.AddObject(cube);
  window.Start(loop);
}