#include "Texture.h"

#include <glad/glad.h>

Texture::Texture(const std::string& filename){
  Image image(filename.c_str(), 0, true);
  Load(image);
}
Texture::Texture(const Image& image){
  Load(image);
}
Texture::~Texture() {
  Unload();
}

bool Texture::Load(const Image& image){
  glGenTextures(1, &m_ID);
  glBindTexture(GL_TEXTURE_2D, m_ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int format = 0;
  switch (image.Channels) {
    case 1: format = GL_RED; break;
    case 2: format = GL_RG; break;
    case 3: format = GL_RGB; break;
    case 4: format = GL_RGBA; break;
    default: break;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, format, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.Pixels);
  return Loaded();
}
void Texture::Unload(){
  glDeleteTextures(1, &m_ID);
}
bool Texture::Loaded() const { return m_ID != 0; }
void Texture::Bind() const {
  glBindTexture(GL_ARRAY_BUFFER, m_ID);
}
void Texture::Unbind() const {
  glBindTexture(GL_ARRAY_BUFFER, 0);
}
