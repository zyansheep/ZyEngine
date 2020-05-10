#pragma once

//Base class for opengl Assets
struct Asset {
  virtual bool Load(const char* filename) = 0;
};