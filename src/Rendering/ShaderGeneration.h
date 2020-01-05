#include "Core/Functions.h"

#define SHADER_TYPE "#version 330 core\n"

namespace ShaderGeneration {
  static Shader Color(){
    std::string vertexShader = std::string(SHADER_TYPE) + R"(
      layout(location = 0) in vec3 a_position;

      uniform mat4 u_transform;
      uniform vec4 u_color;
      
      out vec4 color;
      
      void main() {
        color = u_color;
        gl_Position = u_transform * vec4(a_position, 1);
      }
    )";
    std::string fragShader = std::string(SHADER_TYPE) + R"(
      in vec4 color;
      out vec4 frag_color;

      void main() {
        frag_color = color;
      }
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