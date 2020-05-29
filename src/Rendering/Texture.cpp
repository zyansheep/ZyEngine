#include "Texture.h"

#include <glad/glad.h>
#include "Core/Errors.h"

Texture::Texture(const std::string& filename){
	Load(filename);
}
/*Texture::Texture(const Image& image){
	Load(image);
}*/
Texture::~Texture() {
	DeleteTextures();
}

void Texture::Load(const std::string& filename){
	Load(Image(filename.c_str(), 0, true));
}
void Texture::Load(const Image& image){
	GenTextures(1, GL_TEXTURE_2D);
	Bind();
	Buffer2D(image.Width, image.Height, image.Pixels, image.GetGLChannel());
	SetScaling(GL_LINEAR);
	SetWrapping(GL_CLAMP_TO_EDGE);
	Unbind();
}

bool Texture::Loaded() const {
	return (m_Textures[0] != 0);
}
// Set scaling Parameters texture (Bind Texture First)
void Texture::SetScaling(const unsigned int& scale_type) const {
	SetParameter(GL_TEXTURE_MAG_FILTER, scale_type);
	SetParameter(GL_TEXTURE_MIN_FILTER, scale_type);
}
// Set Wrapping parameters for texture (Bind Texture First)
void Texture::SetWrapping(const unsigned int& wrap_type) const {
	SetParameter(GL_TEXTURE_WRAP_S, wrap_type);
	SetParameter(GL_TEXTURE_WRAP_T, wrap_type);
	SetParameter(GL_TEXTURE_WRAP_R, wrap_type);
}

// Create Textures
void Texture::GenTextures(const unsigned int& size, const unsigned int& type){
	//Don't regenerate new textures if number of textures allready there
	m_Type = type;
	if(m_Textures.size() == size){ return; }
	//Delete old textures if need to regenerate new ones
	if(m_Textures.size() != size && m_Textures.size() != 0){
		DeleteTextures();
	}
	m_Textures.resize(size);
	glGenTextures(size, &m_Textures[0]);
	ZY_GL_ERROR("glGenTextures Failed");
}
// Delete Textures
void Texture::DeleteTextures(){
	glDeleteTextures(m_Textures.size(), &m_Textures[0]);
	ZY_GL_ERROR("glDeleteTextures Failed");
}

// Buffer raw data into texture (Bind Texture First)
void Texture::Buffer1D(const unsigned int& width, const void* pixels, const unsigned int& format) const {
	glTexImage1D(m_Type, 0, format, width, 0, format, GL_UNSIGNED_BYTE, pixels);
	ZY_GL_ERROR("glTexImage1D Failed");
}
void Texture::Buffer2D(const unsigned int& width, const unsigned int& height, const void* pixels, const unsigned int& format) const {
	glTexImage2D(m_Type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	ZY_GL_ERROR("glTexImage2D Failed");
}
void Texture::Buffer3D(const unsigned int& width, const unsigned int& height, const unsigned int& depth, const void* pixels, const unsigned int& format) const {
	glTexImage3D(m_Type, 0, format, width, height, depth, 0, format, GL_UNSIGNED_BYTE, pixels);
	ZY_GL_ERROR("glTexImage3D Failed");
}
// Set OpenGL Integer Parameter (Bind Texture First)
void Texture::SetParameter(const unsigned int& pname, const unsigned int& param) const {
	glTexParameteri(m_Type, pname, param);
	ZY_GL_ERROR("glTexParameteri Failed");
}
// Set OpenGL Float Parameter (Bind Texture First)
void Texture::SetParameter(const unsigned int& pname, const float& param) const {
	glTexParameterf(m_Type, pname, param);
	ZY_GL_ERROR("glTexParameterf Failed");
}
// Bind OpenGL Texture
void Texture::Bind() const {
	glBindTexture(m_Type, m_Textures[0]);
	ZY_GL_ERROR("glBindTexture Failed");
}
void Texture::BindToUnit(const unsigned int& unit) const {
	SetActive(unit);
	Bind();
}
// Unbind OepnGL Texture
void Texture::Unbind() const {
	glBindTexture(m_Type, 0);
	ZY_GL_ERROR("glUnbindTexture Failed");
}

void Texture::SetActive(const unsigned int& unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	ZY_GL_ERROR("glActiveTexture Failed");
}

unsigned int Texture::GetType() const {
	return m_Type;
}