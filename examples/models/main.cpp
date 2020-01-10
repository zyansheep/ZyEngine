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

Model suzanneModel = ModelGeneration::ObjFile("examples/models/suzanne.obj");
Object* suzanne;

Shader shader;

void setup(){
  //shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
  shader = ShaderGeneration::Color();
  cubeModel.Load();
  cube = new Object(cubeModel.GetVertexArray(), shader);
  
  sphereModel.Load();
  sphere = new Object(sphereModel.GetVertexArray(), shader);
  sphere->Translate(glm::vec3(0, 5, 0));
  
  suzanneModel.Load();
  suzanne = new Object(suzanneModel.GetVertexArray(), shader);
  suzanne->Translate(glm::vec3(5, 0, 0));
  
  world.AddObject(cube);
  world.AddObject(sphere);
  world.AddObject(suzanne);
  
  controller.Bind(&camera);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void loop(){
  glClearColor(255,255,255,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  if(window.GetKey(GLFW_KEY_R)){
    controller.Unbind();
    camera = Camera(&window, glm::vec3{0, 0, 8});
    controller.Bind(&camera);
  }
  if(window.GetKey(GLFW_KEY_ESCAPE)){
    controller.Unbind();
  }
  if(window.GetKey(GLFW_KEY_B)){
    controller.Bind(&camera);
  }
  controller.Update();
  
  world.Render();
  world.Draw();
}

int main(){
  setup();
  window.Start(loop);
}