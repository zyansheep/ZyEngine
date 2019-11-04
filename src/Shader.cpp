#include <iostream>
#include <glad/glad.h>
#include <vector>

#include "Functions.cpp"

class Shader {
public:
  Shader(const std::string& vertexShader, const std::string& fragmentShader){
    program = glCreateProgram();
    printGlError("glCreateProgram");
    
    unsigned int vertexId = CompileShader(GL_VERTEX_SHADER, vertexShader);
    if(vertexId == 0){
      std::cout << "[Shader] Compile Error for type: GL_VERTEX_SHADER" << '\n';
      return;
    }
    glAttachShader(program, vertexId);
    printGlError("AttachShader");
    
    unsigned int fragmentId = CompileShader(GL_VERTEX_SHADER, fragmentShader);
    if(fragmentId == 0){
      std::cout << "[Shader] Compile Error for type: GL_FRAGMENT_SHADER" << '\n';
      return;
    }
    glAttachShader(program, fragmentId);
    printGlError("AttachShader");
    
    
    glLinkProgram(program);
    printGlError("LinkProgram");
    
    glValidateProgram(program);
    
    printGlError("ValidateProgram");
  }
  unsigned int program;
  
  //const std::string& source MUST NOT BE DESTROYED!!!
  static unsigned int CompileShader(unsigned int type, const std::string& source){
    //Register a new OpenGL shader
    unsigned int id = glCreateShader(type);
    printGlError("glCreateShader");
    const char* src = source.c_str();
    
    //source id, length of array, array of source ptrs, array of lengths of source ptrs.
    glShaderSource(id, 1, &src, nullptr); //nullptr signifies source is null-terminated
    printGlError("ShaderSource");
    
    //Error handling
    int Result;
    int InfoLogLength;
    glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::cout << "Shader Compile Failed" << '\n';
      std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      printf("%s\n", &VertexShaderErrorMessage[0]);
      
      return 0;
    }
    
    return id;
  }
  
  void use(){
    glUseProgram(program);
  }
};