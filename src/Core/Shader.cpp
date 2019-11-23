#include <iostream>

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Functions.cpp"
#pragma once

class Shader {
public:
  Shader(){};
  Shader(const std::string& vertexPath, const std::string& fragmentPath){
    std::string VertexShaderSource = readFileSync(vertexPath);
    std::string FragmentShaderSource = readFileSync(fragmentPath);
    printf("Compiling shader : %s\n", vertexPath.c_str());
    unsigned int VertexID;
    CompileShader(VertexID, GL_VERTEX_SHADER, VertexShaderSource.c_str());
    
    printf("Compiling shader : %s\n", fragmentPath.c_str());
    unsigned int FragmentID;
    CompileShader(FragmentID, GL_FRAGMENT_SHADER, FragmentShaderSource.c_str());
    
    printf("Linking program\n");
    CompileProgram(program, {&VertexID, &FragmentID});
    
    getMVPMatrixLocation();
  }
  unsigned int program;
  
  static void CompileProgram(unsigned int &ProgramID, std::vector<unsigned int*> shaders){
    ProgramID = glCreateProgram();
    for(int i=0;i<shaders.size();i++){
      glAttachShader(ProgramID, *(shaders[i]));
    }
  	
  	glLinkProgram(ProgramID);
    
    int Result = GL_FALSE;
    int InfoLogLength;
    
  	// Check the program
  	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  	if ( InfoLogLength > 0 ){
  		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
  		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
  		printf("%s\n", &ProgramErrorMessage[0]);
  	}
  }
  static void CompileShader(unsigned int &ShaderID, unsigned int type, const std::string& source){
    ShaderID = glCreateShader(type);
    
    int Result = GL_FALSE;
  	int InfoLogLength;

  	// Compile Shader
  	char const * sourcePointer = source.c_str();
  	glShaderSource(ShaderID, 1, &sourcePointer , NULL);
  	glCompileShader(ShaderID);

  	// Check Vertex Shader
  	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
  	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  	if ( InfoLogLength > 0 ){
  		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
  		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
  		printf("%s\n", &ShaderErrorMessage[0]);
  	}
  }
  
  void use(){
    glUseProgram(program);
  }
  unsigned int MVPMatrixLocation;
  unsigned int getMVPMatrixLocation(){
    if(MVPMatrixLocation == 0){
      MVPMatrixLocation = getUniformLocation("MVPMatrix");
    }
    return MVPMatrixLocation;
  }
  unsigned int getUniformLocation(const char* uniform_handle){
    return glGetUniformLocation(program, uniform_handle);
  }
  
  //#include "UniformFunctions.cpp" //Import uniform functions
  //Primitive
  void Uniform(unsigned int location, float toSend){
    glUniform1f(location, toSend);
  }
  void Uniform(unsigned int location, int toSend){
    glUniform1i(location, toSend);
  }
  void Uniform(unsigned int location, unsigned int toSend){
    glUniform1ui(location, toSend);
  }

  //Vectors length 2
  void Uniform(unsigned int location, glm::vec<2, float> &toSend){
    glUniform2fv(location, 1, glm::value_ptr(toSend));
  }
  void Uniform(unsigned int location, glm::vec<2, int> &toSend){
    glUniform2iv(location, 1, glm::value_ptr(toSend));
  }
  void Uniform(unsigned int location, glm::vec<2, unsigned int> &toSend){
    glUniform2uiv(location, 1, glm::value_ptr(toSend));
  }

  //Vectors length 3
  void Uniform(unsigned int location, glm::vec<3, float> &toSend){
    glUniform3fv(location, 1, glm::value_ptr(toSend));
  }
  void Uniform(unsigned int location, glm::vec<3, int> &toSend){
    glUniform3iv(location, 1, glm::value_ptr(toSend));
  }
  void Uniform(unsigned int location, glm::vec<3, unsigned int> &toSend){
    glUniform3uiv(location, 1, glm::value_ptr(toSend));
  }

  //Vectors length 4
  void Uniform(unsigned int location, glm::vec<4, float> &toSend){
    glUniform4fv(location, 1, glm::value_ptr(toSend));
  }
  void Uniform(unsigned int location, glm::vec<4, int> &toSend){
    glUniform4iv(location, 1, glm::value_ptr(toSend));
  }
  void Uniform(unsigned int location, glm::vec<4, unsigned int> &toSend){
    glUniform4uiv(location, 1, glm::value_ptr(toSend));
  }

  //Matrixes
  void Uniform(unsigned int location, glm::mat4 &toSend){
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(toSend) );
  }

};