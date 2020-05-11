#pragma once

//Base Class for ZyEngine Assets
struct Asset {
  virtual bool Load(const char* filename) = 0;
  virtual bool Load(std::string& filename){ return Load(filename.c_str()); }
  virtual void Unload() = 0;
};