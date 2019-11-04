#include <iostream>
#include <glad/glad.h>
#include <vector>

class Shader {
public:
  Shader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    std::string sources[] = {vertexShader, fragmentShader};
    Shader(2, types, sources);
  }
  Shader(unsigned int count, unsigned int* typeArray, std::string* sourceArray){
    program = glCreateProgram();
    for(int i=0;i<count;i++){
      unsigned int id = CompileShader(typeArray[i], sourceArray[i]);
      if(id == 0){
        std::cout << "[Shader] Compile Error for type:" << typeArray[i] << '\n';
        return;
      }
      glAttachShader(program, id);
    }
    
    glLinkProgram(program);
    glValidateProgram(program);
  }
  unsigned int program;
  
  //const std::string& source MUST NOT BE DESTROYED!!!
  static unsigned int CompileShader(unsigned int type, const std::string& source){
    //Register a new OpenGL shader
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    
    //source id, length of array, array of source ptrs, array of lengths of source ptrs.
    glShaderSource(id, 1, &src, nullptr); //nullptr signifies source is null-terminated
    
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