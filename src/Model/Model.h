#include <vector>
#include <glm/glm.hpp>

#include "Rendering/VertexArray.h"
#include "Rendering/Texture.h"

class Model {
public:
  Model(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices)
  :Vertices(vertices), Indices(indices){}
  ~Model(){}
  
  std::vector<glm::vec3> Vertices;
  std::vector<glm::uvec3> Indices;
  std::vector<glm::vec2> UVs;
  std::vector<glm::vec3> Normals;
  
  std::shared_ptr<VertexArray> MakeVertexArray();
};

namespace ModelGeneration {
	Model Square(float ex, float ey, glm::vec3 position = glm::vec3(0.0f));
	Model Icosphere(unsigned int recursionLevel);
	Model Cube();
	Model ObjFile(std::string path);
};