#include "Core/Window.h"
#include "Core/Gui.h"

//Window (Width, Height, Title)
Window window = Window(1280, 720, "Examples - Template");

Gui gui = Gui(window);

ImVec4 clearColor = ImVec4(0.5,0.5,1.0,1.0);

void setup(){
  gui.Init();
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void loop(){
  glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  gui.StartFrame();
  ImGui::Begin("Hello There~");
    ImGui::Button("This is a button");
    ImGuiColorEditFlags misc_flags = (0) | (ImGuiColorEditFlags_NoDragDrop) | (ImGuiColorEditFlags_AlphaPreviewHalf) | (ImGuiColorEditFlags_NoOptions);
    ImGui::ColorPicker4("##picker", (float*)&clearColor, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
    ImGui::Text("FrameTime: %f seconds", window.GetFrameTime());
    ImGui::Text("Mouse Position: (%d, %d)", window.MouseX, window.MouseY);
    ImGui::Text("Current Time: %f", window.RunTime);
  ImGui::End();
  gui.Render();
  gui.Draw();
}

int main(){
  setup();
  window.Start(loop);
}