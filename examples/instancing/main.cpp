#include "World/World.h"
#include "World/CameraController.h"
#include "Model/Model.h"

//Window (Width, Height, Title)
Window window = Window(1280, 720, "Examples - Instancing");

//Camera (See Camera.h for properties)
Camera camera = Camera(&window, glm::vec3{0, 0, 8});

CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Shader shader;
Model sphereModel = ModelGeneration::Icosphere(4);
Object* sphere;

void setup(){
  shader = ShaderGeneration::File("examples/instancing/main.vert", "examples/instancing/main.frag");
  //Load and initialize objects
  sphere = new Object(sphereModel.MakeVertexArray(), shader);
  
  int gridSize = 10;
  int gridSpace = 3;
  std::vector<glm::vec3> positions;
  positions.reserve(gridSize * gridSize * gridSize);
  for(int i=0;i<gridSize;i++){
    for(int j=0;j<gridSize;j++){
      for(int k=0;k<gridSize;k++){
        positions.push_back(glm::vec3{i*gridSpace, j*gridSpace, k*gridSpace});
      }
    }
  }
  
  sphere->MatrixArray.resize(positions.size(), glm::mat4(1.0f));
  for(uint i=0;i<positions.size();i++){
    sphere->Translate(positions[i], i);
  }
  world.AddObject(sphere);
  
  controller.Bind(&camera);
  
  
  //Enable depth culling
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void loop(){
  //Background Color (R,G,B,A)
  glClearColor(0,0,0,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //Camera binding and unbinding
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
  
  //Update Controller input from OpenGL
  controller.Update();
  
  //Render and Draw World
  world.Render();
  world.Draw();
}

int main(){
  setup();
  window.Start(loop);
}