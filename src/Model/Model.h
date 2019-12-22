
class Model {
public:
  Model(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices)
  :Vertices(vertices), Indices(indices){
    
  }
  
  std::vector<glm::vec3> Vertices;
  std::vector<glm::uvec3> Indices;
  std::vector<glm::vec2> UVs;
  
  void Load(){
    if(m_VertexArray == NULL){
      Buffer* vertexBuffer = new Buffer({{ShaderType::Float3, "a_position"}});
      vertexBuffer->SetData(&Vertices[0], sizeof(glm::vec3) * Vertices.size());
      Buffer* indexBuffer = new Buffer();
      indexBuffer->SetData(&Indices[0], sizeof(glm::uvec3) * Indices.size());
      m_VertexArray = new VertexArray({vertexBuffer}, indexBuffer);
    }
  }
  void Unload(){
    if(m_VertexArray != NULL){
      delete m_VertexArray;
    }
  }
  VertexArray* GetVertexArray(){
    return m_VertexArray;
  }
private:
  VertexArray *m_VertexArray;
};

#include "ModelGenerator.h"