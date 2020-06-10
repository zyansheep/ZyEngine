#pragma once

#include <string>
#include <vector>

#include "Asset/Image.h"

//Texture can be any of 1D, 2D, 3D, Cube Map
class Texture{
public:
	Texture();
	Texture(const std::string& filename);
	//Texture(const Image& image);
	~Texture();

	void Load(const std::string& filename);
	void Load(const Image& image);

	void SetScaling(const unsigned int& scale_type) const;
	void SetWrapping(const unsigned int& wrap_type) const;

	void GenTextures(const unsigned int& size, const unsigned int& type);
	void DeleteTextures();
	void Buffer1D(const unsigned int& width, const void* pixels, const unsigned int& format) const;
	void Buffer2D(const unsigned int& width, const unsigned int& height, const void* pixels, const unsigned int& format) const;
	void Buffer3D(const unsigned int& width, const unsigned int& height, const unsigned int& depth, const void* pixels, const unsigned int& format) const;
	void SetParameter(const unsigned int& pname, const unsigned int& param) const;
	void SetParameter(const unsigned int& pname, const float& param) const;
	void Bind() const;
	void BindToUnit(const int& unit) const;
	void Unbind() const;

	static void SetActive(const int& unit);
private:
	unsigned int m_Type;
	std::vector<unsigned int> m_Textures;
public:
	unsigned int GetType() const;
};