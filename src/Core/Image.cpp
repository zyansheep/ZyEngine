#include "Image.h"

#include <stb_image.h>

Image::~Image(){
  stbi_image_free(Pixels);
}
bool Image::Load(const char* filename, int desired_channels, bool flip){
  stbi_set_flip_vertically_on_load(flip);
  Pixels = stbi_load(filename, &Width, &Height, &Channels, desired_channels);
  return !Pixels;
};
GLFWimage Image::CreateGLFWImage(){
  return {Width, Height, Pixels};
}