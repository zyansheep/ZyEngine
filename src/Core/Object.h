
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glad/glad.h"

#include "Rendering/VertexArray.h"
#include "Rendering/Shader.cpp"
#include "Camera.h"

#pragma once

class Object {
public:
  Object(){};
  Object(VertexArray* vertexArray, Shader* shader, std::string MVPString = "MVPMatrix")
  : m_VertexArray(vertexArray), m_Shader(shader){
    m_MVPLocation = shader->GetUniformLocation(MVPString.c_str());
  }
  void render(Camera* viewport){
    m_MVPMatrix = viewport->matrix * m_ModelMatrix;
  }
  void draw(){
    m_Shader->Bind();
    m_Shader->Uniform(m_MVPLocation, m_MVPMatrix);
    m_VertexArray->Draw();
  }
  
private:
  int m_MVPLocation;
  glm::mat4 m_MVPMatrix;
  glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
  
  VertexArray* m_VertexArray;
  Shader* m_Shader;
};
