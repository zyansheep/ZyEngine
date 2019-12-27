#include "World/World.h"
#include "World/CameraController.h"

//Window (Width, Height, Title)
Window window = Window(1280, 720, "Examples - Template");

//Camera (See Camera.h for properties)
Camera camera = Camera(&window, glm::vec3{0, 0, 8});

CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Shader shader;

void setup(){
  //shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
  
  //Load and initialize objects
  /*
  model.Load();
  object = new Object(cubeModel.GetVertexArray(), shader);
  */
  
  //controller.Bind(&camera);
  
  //Enable depth culling
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void loop(){
  //Background Color (R,G,B,A)
  glClearColor(0,0,0,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //Update Controller input from OpenGL
  //controller.Update();
  
  //Render and Draw World
  world.Render();
  world.Draw();
}

int main(){
  setup();
  window.Start(loop);
}