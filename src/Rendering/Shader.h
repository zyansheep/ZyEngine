#include <iostream>

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
  Shader();
  Shader(const std::string& vertexSource, const std::string& fragmentSource);
  unsigned int program;
  
  void CompileShader(unsigned int &ShaderID, unsigned int type, const std::string& source);
  static void CompileProgram(unsigned int &ProgramID, std::vector<unsigned int*> shaders);
  
  void Bind();
  int GetUniformLocation(const char* uniform_handle);
  
  //#include "UniformFunctions.cpp" //Import uniform functions
  //Primitive
  void Uniform(int location, float toSend);
  void Uniform(int location, int toSend);
  void Uniform(int location, unsigned int toSend);

  //Vectors length 2
  void Uniform(int location, glm::vec<2, float> toSend);
  void Uniform(int location, glm::vec<2, int> toSend);
  void Uniform(int location, glm::vec<2, unsigned int> toSend);

  //Vectors length 3
  void Uniform(int location, glm::vec<3, float> toSend);
  void Uniform(int location, glm::vec<3, int> toSend);
  void Uniform(int location, glm::vec<3, unsigned int> toSend);

  //Vectors length 4
  void Uniform(int location, glm::vec<4, float> toSend);
  void Uniform(int location, glm::vec<4, int> toSend);
  void Uniform(int location, glm::vec<4, unsigned int> toSend);
  
  //Matrixes
  void Uniform(int location, glm::mat4 toSend);
};

#include "ShaderGeneration.h"