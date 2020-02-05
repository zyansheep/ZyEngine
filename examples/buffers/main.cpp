#include "World/World.h"
#include "World/CameraController.h"

Window window = Window(1280,720, "Examples - Buffers");

Camera camera = Camera(&window, glm::vec3{0, 0, 8});
CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Object* cube;
Shader shader;

#include "attributes.cpp"

void setup(){
  shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
  
  Buffer* cube_positions = new Buffer({{ShaderType::Float3, "a_position"}});
  
  //Tell Renderer to create new buffer on graphics card
  //Call buffer->Modify(void* data, size_t size, size_t offset) to modify the allocated data
  cube_positions->New((float*)cube_vertices_, sizeof(cube_vertices_));
  Buffer* cube_colors = new Buffer({{ShaderType::Float3, "a_color"}});
  cube_colors->New((float*)cube_colors_, sizeof(cube_colors_));
  cube = new Object(new VertexArray({cube_positions, cube_colors}), shader);
  
  world.AddObject(cube);
  
  controller.Bind(&camera);
}

void loop(){
  glClearColor(255,255,255,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  controller.Update();
  
  world.Render();
  world.Draw();
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

int main(){
  setup();
  window.Start(loop);
}