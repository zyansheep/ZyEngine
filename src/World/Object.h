#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

#include "Rendering/VertexArray.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

#include "Camera.h"

class Object {
public:
	Object();
	Object(const std::shared_ptr<VertexArray>& vertexArray, Shader& shader, std::string modelUniform = "u_matrix");
	Object(const std::shared_ptr<VertexArray>& vertexArray, Shader& shader, std::vector<Texture*> textures, std::string modelUniform = "u_matrix");
	
	void Render(const Camera& viewport);
	void Draw();
	
	void Rotate(float degrees, glm::vec3 axis, unsigned int index = 0);
	void Translate(glm::vec3 v, unsigned int index = 0);
	void Scale(glm::vec3 factor, unsigned int index = 0);
	
	std::vector<glm::mat4> MatrixArray = {glm::mat4(1.0f)}; //Positions of object (if greater than 1, render() will generate InstanceBuffer)
private:
	std::vector<glm::mat4> m_MVPVec = {glm::mat4(1.0f)};
	//Using Uniforms for single matrix, attributes for instanced rendering
	int m_MatrixLocation; //Uniform Location of Model Matrix
	glm::mat4 m_MVP;
	
	std::shared_ptr<VertexArray> m_VertexArray; //NOT MANAGED BY Object.h
	
	Shader& m_Shader;
	std::vector<Texture*> m_Textures;
};
