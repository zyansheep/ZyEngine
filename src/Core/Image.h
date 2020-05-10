#pragma once

#include <GLFW/glfw3.h>
#include "Asset.h"

struct Image : public Asset {
  Image(const char* filename){Load(filename);}
  ~Image();
  bool Load(const char* filename){ return Load(filename, 0); }
  bool Load(const char* filename, int desired_channels, bool flip = false);
  GLFWimage CreateGLFWImage();
  int Width;
  int Height;
  int Channels;
  unsigned char* Pixels;
};