#include <iostream>
#include <vector>
#include <array>
#include <math.h>

#include "Core/World.h"
#include "Core/CameraController.h"
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

//unsigned int shader;
//unsigned int tri_vao;

//float ScaleCount = 1.0f;
//Vertex<float, 2> transition = {0.0f, 0.0f};
//unsigned int main_uniform_scale;
//unsigned int main_uniform_transition;

Window window = Window(1280,720, "Graphics Engine Testing");
Camera camera = Camera(&window, glm::vec3{0, 0, 8});
CameraController controller = CameraController(&window);
World world = World(&window, &camera);

Object* plane;
Object* cube;
Object* cube2;
Shader shader;

ImVec4 clearColor = ImVec4(0.5,0.5,1.0,1.0);

#include "cube.cpp"
void setup(){
  //controller.Bind(&camera);
  //Triangle vertex positions
  //shader = Shader("../../src/shaders/main.vert","../../src/shaders/main.frag");
  shader = Shader("src/shaders/main.vert", "src/shaders/main.frag");
  
  Buffer* cube_positions = new Buffer({{ShaderType::Float3, "a_position"}});
  cube_positions->SetData((float*)cube_vertices_, sizeof(cube_vertices_));
  Buffer* cube_colors = new Buffer({{ShaderType::Float3, "a_color"}});
  cube_colors->SetData((float*)cube_colors_, sizeof(cube_colors_));
  cube = new Object(new VertexArray({cube_positions, cube_colors}), shader);
  cube2 = new Object(new VertexArray({cube_positions, cube_colors}), shader);
  cube->Translate(glm::vec3(0, 5, 0));
  
  Buffer* plane_attrib_buffer = new Buffer({
    {ShaderType::Float3, "a_position"},
    {ShaderType::Float3, "a_color"}
  });
  float plane_attrib_array[] = {
    0,  0,  0,  255,  0,  0,
    0,  0,100,    0,255,  0,
    0,100,100,    0,  0,255,
    0,100,  0,  255,  0,255
  };
  plane_attrib_buffer->SetData(plane_attrib_array, sizeof(plane_attrib_array));
  
  Buffer* plane_index_buffer = new Buffer();
  uint plane_index_array[] {
    0,1,2,
    0,2,3
  };
  plane_index_buffer->SetData(plane_index_array, sizeof(plane_index_array));
  
  plane = new Object(new VertexArray({plane_attrib_buffer}, plane_index_buffer), shader);
  plane->Rotate(90.0f, glm::vec3(0,0,1));
  plane->Translate({-8,-50,-50});
  
  world.AddObject(cube);
  world.AddObject(cube2);
  world.AddObject(plane);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window.GetNative(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
}

void loop(){
  glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  controller.Update();
  
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
  cube->Rotate(90.0f/60, glm::vec3(0.0f, 0.0f, 1.0f));
  
  world.Render();
  world.Draw();
  
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  // render your GUI
  ImGui::Begin("Hello There");
    ImGui::Button("This is a button");
    ImGuiColorEditFlags misc_flags = (0) | (ImGuiColorEditFlags_NoDragDrop) | (ImGuiColorEditFlags_AlphaPreviewHalf) | (ImGuiColorEditFlags_NoOptions);
    ImGui::ColorPicker4("##picker", (float*)&clearColor, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
    ImGui::Text("FrameTime: %f seconds", window.GetFrameTime());
    ImGui::Text("Mouse Position: (%d, %d)", window.MouseX, window.MouseY);
    ImGui::Text("Current Time: %f", window.RunTime);
  ImGui::End();

  // Render dear imgui into screen
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(void){
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  setup();
  window.Start(loop);
}
