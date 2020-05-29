#pragma once

#include <string>

#include "imgui.h"

#include "Window.h"

class Gui {
public:
  Gui(Window& window);
  ~Gui();
  void Init(bool styleDark = true);
  void StartFrame();
  void Render();
  void Draw();
  ImGuiIO* io; //This pointer is managed by imgui
};