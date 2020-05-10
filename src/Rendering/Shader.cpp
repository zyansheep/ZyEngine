#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Functions.h"

Shader::Shader(){}
Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource){
  unsigned int VertexID;
  CompileShader(VertexID, GL_VERTEX_SHADER, vertexSource.c_str());
  
  unsigned int FragmentID;
  CompileShader(FragmentID, GL_FRAGMENT_SHADER, fragmentSource.c_str());
  
  //printf("Compiling Shader\n");
  CompileProgram(m_ID, {&VertexID, &FragmentID});
}

void Shader::CompileProgram(unsigned int &ProgramID, std::vector<unsigned int*> shaders){
  ProgramID = glCreateProgram();
  for(unsigned int i=0;i<shaders.size();i++){
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
void Shader::CompileShader(unsigned int &ShaderID, unsigned int type, const std::string& source){
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

void Shader::Bind(){
  glUseProgram(m_ID);
}
void Shader::Unbind(){
  glUseProgram(0);
}
int Shader::GetUniformLocation(const char* uniform_handle){
  return glGetUniformLocation(m_ID, uniform_handle);
}
void Shader::Uniform(int location, const float toSend){
  glUniform1f(location, toSend);
}
void Shader::Uniform(int location, size_t count, const float* toSend){
  glUniform1fv(location, count, toSend);
}

void Shader::Uniform(int location, const int toSend){
  glUniform1i(location, toSend);
}
void Shader::Uniform(int location, size_t count, const int* toSend){
  glUniform1iv(location, count, toSend);
}

void Shader::Uniform(int location, const unsigned int toSend){
  glUniform1ui(location, toSend);
}
void Shader::Uniform(int location, size_t count, const unsigned int* toSend){
  glUniform1uiv(location, count, toSend);
}

//Vectors length 2
void Shader::Uniform(int location, const glm::vec<2, float> toSend){
  glUniform2fv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<2, float>* toSend){
  glUniform2fv(location, count, (float*)toSend);
}
void Shader::Uniform(int location, const glm::vec<2, int> toSend){
  glUniform2iv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<2, int>* toSend){
  glUniform2iv(location, count, (int*)toSend);
}
void Shader::Uniform(int location, const glm::vec<2, unsigned int> toSend){
  glUniform2uiv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<2, unsigned int>* toSend){
  glUniform2uiv(location, count, (unsigned int*)toSend);
}

//Vectors length 3
void Shader::Uniform(int location, const glm::vec<3, float> toSend){
  glUniform3fv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<3, float>* toSend){
  glUniform3fv(location, count, (float*)toSend);
}
void Shader::Uniform(int location, const glm::vec<3, int> toSend){
  glUniform3iv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<3, int>* toSend){
  glUniform3iv(location, count, (int*)toSend);
}
void Shader::Uniform(int location, const glm::vec<3, unsigned int> toSend){
  glUniform3uiv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<3, unsigned int>* toSend){
  glUniform3uiv(location, count, (unsigned int*)toSend);
}

//Vectors length 4
void Shader::Uniform(int location, const glm::vec<4, float> toSend){
  glUniform4fv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<4, float>* toSend){
  glUniform4fv(location, count, (float*)toSend);
}
void Shader::Uniform(int location, const glm::vec<4, int> toSend){
  glUniform4iv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<4, int>* toSend){
  glUniform4iv(location, count, (int*)toSend);
}
void Shader::Uniform(int location, const glm::vec<4, unsigned int> toSend){
  glUniform4uiv(location, 1, glm::value_ptr(toSend));
}
void Shader::Uniform(int location, size_t count, const glm::vec<4, unsigned int>* toSend){
  glUniform4uiv(location, count, (unsigned int*)toSend);
}

//Matrixes
void Shader::Uniform(int location, glm::mat4 toSend){
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(toSend) );
}


Shader ShaderGeneration::Texture(){
  std::string vertexShader = std::string(ZY_SHADER_VERSION) + R"(
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
  std::string fragShader = std::string(ZY_SHADER_VERSION) + R"(
    in vec2 i_texCoord;
    uniform sampler2D u_texture;
    out vec4 frag_color;
    void main() { frag_color = texture(u_texture, i_texCoord); }
  )";
  return Shader(vertexShader, fragShader);
}
Shader ShaderGeneration::Color(){
  std::string vertexShader = std::string(ZY_SHADER_VERSION) + R"(
    layout(location = 0) in vec3 a_position;

    uniform mat4 u_matrix;
    uniform vec4 u_color;
    
    out vec4 i_color;
    
    void main() {
      i_color = u_color;
      gl_Position = u_matrix * vec4(a_position, 1);
    }
  )";
  std::string fragShader = std::string(ZY_SHADER_VERSION) + R"(
    in vec4 i_color;
    out vec4 frag_color;
    void main() { frag_color = i_color; }
  )";
  return Shader(vertexShader, fragShader);
}
Shader ShaderGeneration::Test(){
  std::string vertexShader = std::string(ZY_SHADER_VERSION) + R"(
    layout(location = 0) in vec3 a_position;

    uniform mat4 u_matrix;
    
    out vec3 i_color;
    
    void main() {
      i_color = sin(a_position);
      gl_Position = u_matrix * vec4(a_position, 1);
    }
  )";
  std::string fragShader = std::string(ZY_SHADER_VERSION) + R"(
    in vec3 i_color;
    out vec4 frag_color;
    void main() { frag_color = vec4(i_color, 1.0); }
  )";
  return Shader(vertexShader, fragShader);
}
Shader ShaderGeneration::File(std::string vertexPath, std::string fragmentPath){
  std::string vertexShader = readFileSync(vertexPath);
  std::string fragmentShader = readFileSync(fragmentPath);
  printf("Compiling shader : %s, %s\n", vertexPath.c_str(), fragmentPath.c_str());
  return Shader(vertexShader, fragmentShader);
}
