#include "Gui.h"

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

Gui::Gui(Window& window){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window.GetNative(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
Gui::~Gui(){
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void Gui::Init(bool styleDark){
	// Setup Dear ImGui style
	if(styleDark){
		ImGui::StyleColorsDark();
	}
}
void Gui::StartFrame(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void Gui::Render(){
	ImGui::Render();
}
void Gui::Draw(){
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}