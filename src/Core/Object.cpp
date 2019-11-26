
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glad/glad.h"

#include "VertexArray.cpp"
#include "Shader.cpp"
#include "Camera.cpp"

class Object {
public:
  Object(){};
  Object(VertexArray* vao, Shader* shader)
  : m_vao(vao), m_shader(shader){
    MVPLocation = shader->getMVPMatrixLocation();
  }
  void render(Camera* viewport){
    MVPMatrix = viewport->m_projection * viewport->m_view * modelMatrix;
  }
  void draw(){
    m_shader->use();
    m_shader->Uniform(MVPLocation, MVPMatrix);
    m_vao->draw();
  }
  int MVPLocation;
  glm::mat4 MVPMatrix;
  
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  
  Shader* m_shader;
  VertexArray* m_vao;
};