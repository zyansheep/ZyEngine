#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& filename)
{
  glGenTextures(1, &m_Texture);
  glBindTexture(GL_TEXTURE_2D, m_Texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height, channels;

  stbi_set_flip_vertically_on_load(1);
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

  int format = 0;
  switch (channels)
  {
    case 1:
      format = GL_RED;
      break;
    case 2:
      format = GL_RG;
      break;
    case 3:
      format = GL_RGB;
      break;
    case 4:
      format = GL_RGBA;
      break;
    default:
      break;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_Texture);
}

void Texture::Bind() const
{
  glBindTexture(GL_ARRAY_BUFFER, m_Texture);
}

void Texture::Unbind() const
{
  glBindTexture(GL_ARRAY_BUFFER, 0);
}
