#pragma once

#include <iostream>

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Functions.h"
#include "Asset.h"

class Shader {
public:
  Shader();
  Shader(const std::string& vertexSource, const std::string& fragmentSource);
  
  void CompileShader(unsigned int &ShaderID, unsigned int type, const std::string& source);
  static void CompileProgram(unsigned int &ProgramID, std::vector<unsigned int*> shaders);
  
  void Bind();
  void Unbind();
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
private:
  unsigned int m_ID;
};

#define SHADER_TYPE "#version 330 core\n"

namespace ShaderGeneration {
  static Shader Texture(){
    std::string vertexShader = std::string(SHADER_TYPE) + R"(
      layout(location = 0) in vec3 a_position;
      layout(location = 1) in vec2 a_texCoords;
      
      out vec2 i_texCoord;
      
      uniform mat4 u_matrix;
      
      out vec4 i_color;
      
      void main() {
        i_texCoord = a_texCoords;
        gl_Position = u_matrix * vec4(a_position, 1);
      }
    )";
    std::string fragShader = std::string(SHADER_TYPE) + R"(
      in vec2 i_texCoord;
      uniform sampler2D u_texture;
      out vec4 frag_color;
      void main() { frag_color = texture(u_texture, i_texCoord); }
    )";
    return Shader(vertexShader, fragShader);
  }
  static Shader Color(){
    std::string vertexShader = std::string(SHADER_TYPE) + R"(
      layout(location = 0) in vec3 a_position;

      uniform mat4 u_matrix;
      uniform vec4 u_color;
      
      out vec4 i_color;
      
      void main() {
        i_color = u_color;
        gl_Position = u_matrix * vec4(a_position, 1);
      }
    )";
    std::string fragShader = std::string(SHADER_TYPE) + R"(
      in vec4 i_color;
      out vec4 frag_color;
      void main() { frag_color = i_color; }
    )";
    return Shader(vertexShader, fragShader);
  }
  static Shader Test(){
    std::string vertexShader = std::string(SHADER_TYPE) + R"(
      layout(location = 0) in vec3 a_position;

      uniform mat4 u_matrix;
      
      out vec3 i_color;
      
      void main() {
        i_color = sin(a_position);
        gl_Position = u_matrix * vec4(a_position, 1);
      }
    )";
    std::string fragShader = std::string(SHADER_TYPE) + R"(
      in vec3 i_color;
      out vec4 frag_color;
      void main() { frag_color = vec4(i_color, 1.0); }
    )";
    return Shader(vertexShader, fragShader);
  }
  static Shader File(std::string vertexPath, std::string fragmentPath){
    std::string vertexShader = readFileSync(vertexPath);
    std::string fragmentShader = readFileSync(fragmentPath);
    printf("Compiling shader : %s, %s\n", vertexPath.c_str(), fragmentPath.c_str());
    return Shader(vertexShader, fragmentShader);
  }
}