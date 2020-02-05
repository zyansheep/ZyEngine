#include "Rendering/VertexArray.h"

class Model {
public:
  Model(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices)
  :Vertices(vertices), Indices(indices){
    
  }
  ~Model(){
    //Unload();
  }
  
  std::vector<glm::vec3> Vertices;
  std::vector<glm::uvec3> Indices;
  std::vector<glm::vec2> UVs;
  std::vector<glm::vec3> Normals;
  
  VertexArray* MakeVertexArray(){
    VertexArray* vao = new VertexArray;
    std::cout << "Loading model with " << Vertices.size() <<"  vertices and " << Indices.size() << " indices" << '\n';
    vao->Buffers.push_back(new Buffer({{ShaderType::Float3, "a_position"}}));
    vao->Buffers[0]->New(&Vertices[0], sizeof(glm::vec3) * Vertices.size());
    vao->IndexBuffer = new Buffer;
    vao->IndexBuffer->New(&Indices[0], sizeof(glm::uvec3) * Indices.size());
    vao->Configure();
    return vao;
  }
};

#include "ModelGeneration.h"