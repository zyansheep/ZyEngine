#pragma once

#include <iostream>

#include <vector>

#include <glm/glm.hpp>

#define ZY_SHADER_VERSION "#version 330 core\n"

class Shader {
public:
  Shader();
  Shader(const std::string& vertexSource, const std::string& fragmentSource);
  
  void CompileShader(unsigned int &ShaderID, unsigned int type, const std::string& source);
  static void CompileProgram(unsigned int &ProgramID, std::vector<unsigned int*> shaders);
  
  void Bind();
  void Unbind();
  bool Loaded(){ return (m_ID != 0); }
  int GetUniformLocation(const char* uniform_handle);
  
  //#include "UniformFunctions.cpp" //Import uniform functions
  //Primitive
  void Uniform(int location, const float toSend);
  void Uniform(int location, size_t count, const float* toSend);
  void Uniform(int location, const int toSend);
  void Uniform(int location, size_t count, const int* toSend);
  void Uniform(int location, const unsigned int toSend);
  void Uniform(int location, size_t count, const unsigned int* toSend);

  //Vectors length 2
  void Uniform(int location, const glm::vec<2, float> toSend);
  void Uniform(int location, size_t count, const glm::vec<2, float>* toSend);
  void Uniform(int location, const glm::vec<2, int> toSend);
  void Uniform(int location, size_t count, const glm::vec<2, int>* toSend);
  void Uniform(int location, const glm::vec<2, unsigned int> toSend);
  void Uniform(int location, size_t count, const glm::vec<2, unsigned int>* toSend);

  //Vectors length 3
  void Uniform(int location, const glm::vec<3, float> toSend);
  void Uniform(int location, size_t count, const glm::vec<3, float>* toSend);
  void Uniform(int location, const glm::vec<3, int> toSend);
  void Uniform(int location, size_t count, const glm::vec<3, int>* toSend);
  void Uniform(int location, const glm::vec<3, unsigned int> toSend);
  void Uniform(int location, size_t count, const glm::vec<3, unsigned int>* toSend);

  //Vectors length 4
  void Uniform(int location, const glm::vec<4, float> toSend);
  void Uniform(int location, size_t count, const glm::vec<4, float>* toSend);
  void Uniform(int location, const glm::vec<4, int> toSend);
  void Uniform(int location, size_t count, const glm::vec<4, int>* toSend);
  void Uniform(int location, const glm::vec<4, unsigned int> toSend);
  void Uniform(int location, size_t count, const glm::vec<4, unsigned int>* toSend);
  
  //Matrixes
  void Uniform(int location, glm::mat4 toSend);
private:
  unsigned int m_ID;
};

namespace ShaderGeneration {
  static Shader Texture();
  static Shader Color();
  static Shader Test();
  static Shader File(std::string vertexPath, std::string fragmentPath);
}