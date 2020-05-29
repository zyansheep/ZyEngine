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
  
  void Bind() const;
  void Unbind() const;
  bool Loaded() const;
  int GetUniformLocation(const char* uniform_handle) const;
  int GetUniformLocation(const std::string& uniform_handle) const;
  std::string GetProgramError() const;
  std::string GetShaderError() const;
  
  static std::string VertError;
  static std::string FragError;
  static std::string ProgramError;

  //Primitive
  void Uniform(int location, const float toSend) const;
  void Uniform(int location, size_t count, const float* toSend) const;
  void Uniform(int location, const int toSend) const;
  void Uniform(int location, size_t count, const int* toSend) const;
  void Uniform(int location, const unsigned int toSend) const;
  void Uniform(int location, size_t count, const unsigned int* toSend) const;

  //Vectors length 2
  void Uniform(int location, const glm::vec<2, float> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<2, float>* toSend) const;
  void Uniform(int location, const glm::vec<2, int> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<2, int>* toSend) const;
  void Uniform(int location, const glm::vec<2, unsigned int> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<2, unsigned int>* toSend) const;

  //Vectors length 3
  void Uniform(int location, const glm::vec<3, float> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<3, float>* toSend) const;
  void Uniform(int location, const glm::vec<3, int> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<3, int>* toSend) const;
  void Uniform(int location, const glm::vec<3, unsigned int> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<3, unsigned int>* toSend) const;

  //Vectors length 4
  void Uniform(int location, const glm::vec<4, float> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<4, float>* toSend) const;
  void Uniform(int location, const glm::vec<4, int> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<4, int>* toSend) const;
  void Uniform(int location, const glm::vec<4, unsigned int> toSend) const;
  void Uniform(int location, size_t count, const glm::vec<4, unsigned int>* toSend) const;
  
  //Matrixes
  void Uniform(int location, glm::mat4 toSend) const;
private:
  unsigned int m_ID;
};

namespace ShaderGeneration {
	Shader Texture();
	Shader Color();
	Shader Test();
	Shader File(std::string vertexPath, std::string fragmentPath);
}