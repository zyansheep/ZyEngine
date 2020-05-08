#pragma once

#include <glm/glm.hpp>

class Material {
public:
  glm::vec3 Ambient; //Ambient color (color translation to make up for not ray-tracing)
  glm::vec3 Diffuse; //Actual color of the object
  glm::vec3 Specular; //Make it look shiny, like metal
};
