#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Asset.h"

//Base ZyEngine Image Class 
struct Image : public Asset {
  Image(const std::string& filename, int desired_channels = 0, bool flip = false)
   : Image(filename.c_str(), desired_channels, flip){};
  Image(const char* filename, int desired_channels = 0, bool flip = false);
  Image(){};
  ~Image();

  bool Load(const char* filename){ return Load(filename, 0); }
  bool Load(const char* filename, int desired_channels = 0, bool flip = false);
  void Unload();

  GLFWimage CreateGLFWImage();
  int Width;
  int Height;
  int Channels;
  unsigned char* Pixels;
};