
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glad/glad.h"

#include "Rendering/VertexArray.h"
#include "Rendering/Shader.h"
#include "Camera.h"

#pragma once

class Object {
public:
  Object(VertexArray* vertexArray, Shader& shader, std::string MVPString = "u_transform")
  : m_VertexArray(vertexArray), m_Shader(shader){
    m_MVPLocation = shader.GetUniformLocation(MVPString.c_str());
  }
  void Render(Camera* viewport){
    m_MVPMatrix = viewport->matrix * m_ModelMatrix;
  }
  void Draw(){
    m_Shader.Bind();
    m_Shader.Uniform(m_MVPLocation, m_MVPMatrix);
    m_VertexArray->Draw();
  }
  
  void Rotate(float degrees, glm::vec3 axis){
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(degrees), axis);
  }
  void Translate(glm::vec3 v){
    m_ModelMatrix = glm::translate(m_ModelMatrix, v);
  }
  
  VertexArray* GetVertexArray(){
    return m_VertexArray;
  }
protected:
  int m_MVPLocation;
  glm::mat4 m_MVPMatrix;
  glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
  
  VertexArray* m_VertexArray;
  Shader& m_Shader;
};

#include "ObjectArray.h"
