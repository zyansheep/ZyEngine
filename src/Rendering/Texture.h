#pragma once

#include <string>

class Texture {
public:
  Texture(const std::string& filename);
  ~Texture();
  void Bind() const;
  void Unbind() const;
private:
  unsigned int m_Texture;
};