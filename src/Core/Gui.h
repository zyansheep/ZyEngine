
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

class Gui {
public:
  Gui(Window& window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.GetNative(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
  }
  void Init(bool styleDark = true){
    // Setup Dear ImGui style
    if(styleDark){
      ImGui::StyleColorsDark();
    }
  }
  void Begin(std::string name){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // render your GUI
    ImGui::Begin(name.c_str());
  }
  void End(){
    ImGui::End();
  }
  void Render(){
    ImGui::Render();
  }
  void Draw(){
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
  ImGuiIO* io;
};