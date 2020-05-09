#pragma once

#include <string>
#include <memory>

//#include "Asset.h"

class Texture{
public:
  Texture(const std::string& filename);
  static std::shared_ptr<Texture> New(const std::string& filename);
  ~Texture();
  void Bind() const;
  void Unbind() const;
private:
  unsigned int m_ID;
};