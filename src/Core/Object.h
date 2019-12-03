
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
  Object(VertexArray* vao, Shader* shader)
  : m_vao(vao), m_shader(shader){
    MVPLocation = shader->GetUniformLocation("MVPMatrix");
  }
  void render(Camera* viewport){
    MVPMatrix = viewport->matrix * modelMatrix;
  }
  void draw(){
    m_shader->Bind();
    m_shader->Uniform(MVPLocation, MVPMatrix);
    m_vao->Draw();
  }
  int MVPLocation;
  glm::mat4 MVPMatrix;
  
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  
  Shader* m_shader;
  VertexArray* m_vao;
};