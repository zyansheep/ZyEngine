
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glad/glad.h"

#include "VertexArrayObject.cpp"
#include "Shader.cpp"

class Object {
public:
  Object(){};
  Object(VertexArrayObject* vao, Shader* shader)
  : m_vao(vao), m_shader(shader){
    
  }
  void render(glm::mat4 &VPMatrix){
    MVPMatrix = modelMatrix * VPMatrix;
  }
  void draw(){
    m_shader->Uniform(m_shader->MVPMatrixLocation, MVPMatrix);
    m_shader->use();
    m_vao->draw();
  }
  glm::mat4 MVPMatrix;
  
  glm::mat4 modelMatrix;
  
  Shader* m_shader;
  VertexArrayObject* m_vao;
};