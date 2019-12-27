#include "World/World.h"
#include "World/CameraController.h"
#include "Model/Model.h"

Window window = Window(1280,720, "Examples - Models");

Camera camera = Camera(&window, glm::vec3{0, 0, 8});
CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Model cubeModel = ModelGeneration::Cube();
Object* cube;

Model sphereModel = ModelGeneration::Icosphere(4);
Object* sphere;

Shader shader;

void setup(){
  shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
  
  cubeModel.Load();
  cube = new Object(cubeModel.GetVertexArray(), shader);
  
  sphereModel.Load();
  sphere = new Object(sphereModel.GetVertexArray(), shader);
  sphere->Translate(glm::vec3(0, 5, 0));
  
  world.AddObject(cube);
  world.AddObject(sphere);
  
  controller.Bind(&camera);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void loop(){
  glClearColor(255,255,255,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  controller.Update();
  
  world.Render();
  world.Draw();
}

int main(){
  setup();
  window.Start(loop);
}