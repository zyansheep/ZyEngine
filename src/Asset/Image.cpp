#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const char* filename, int desired_channels, bool flip){
  Load(filename, desired_channels, flip);
}
Image::~Image(){
  Unload();
}
bool Image::Load(const char* filename, int desired_channels, bool flip){
  stbi_set_flip_vertically_on_load(flip);
  Pixels = stbi_load(filename, &Width, &Height, &Channels, desired_channels);
  return !Pixels;
};
void Image::Unload(){
  stbi_image_free(Pixels);
};
GLFWimage Image::CreateGLFWImage() const {
  return {Width, Height, Pixels};
}

#include <glad/glad.h>
unsigned int Image::GetGLChannel() const{
	switch (Channels) {
		case 1: return GL_RED;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4: return GL_RGBA;
	}
	return 0;
}