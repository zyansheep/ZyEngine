#include "World/World.h"
#include "World/CameraController.h"
#include "Rendering/Texture.h"
#include "Model/Model.h"

#include "Core/Image.h"

//Window (Width, Height, Title)
Window window = Window(1280, 720, "Examples - Texture");

//Camera (See Camera.h for properties)
Camera camera = Camera(&window, glm::vec3{0, 0, 8});
//Camera2D camera = Camera(&window, glm::vec2{0,0});

//CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Shader shader;

std::shared_ptr<Texture> texture = Texture::New("examples/texture/tex.png");
Shader textureShader = ShaderGeneration::Texture();
Model plane = ModelGeneration::Square(0.5,0.5);
Object* object;

void setup(){
  Image image("/home/zyansheep/Pictures/Logo.png");
  window.SetIcons(&image, 1);
  camera.Properties.Ortho = true;
  //shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
  plane.UVs = {
    {0,0},
    {0,1},
    {1,1},
    {1,0}
  };
  object = new Object(plane.MakeVertexArray(), textureShader, {texture});
  world.AddObject(object); //Make sure to add any objects you created to the world
  
  //controller.Bind(&camera);
  
  
  //Enable depth culling
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void draw(){
  //Background Color (R,G,B,A)
  glClearColor(0,0,0,255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //Update Controller input from glfw
  //controller.Update();
  //object->MatrixArray[0] = glm::mat4(1.0f);
  //object->Rotate(glfwGetTime()*180, {0,0,1});
  
  //Render and Draw World
  world.Render();
  world.Draw();
}

int main(){
  setup();
  window.Start(draw);
}