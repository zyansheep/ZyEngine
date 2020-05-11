#pragma once

#include <string>
#include <memory>

#include "Core/Image.h"

class Texture{
public:
  Texture(const std::string& filename);
  Texture(const Image& image);
  ~Texture();

  bool Load(const Image& image);
  void Unload();
  bool Loaded() const;
  
  void Bind() const;
  void Unbind() const;
private:
  unsigned int m_ID;
};