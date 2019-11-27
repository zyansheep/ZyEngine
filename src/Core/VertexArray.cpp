#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

//#include "Objects.cpp"
#include "Shader.cpp"

class VertexBuffer {
public:
  VertexBuffer(std::vector<glm::vec3> vertices, unsigned int typeDraw = GL_DYNAMIC_DRAW){
    size = vertices.size();
    glGenBuffers(1, &address);
    Bind();
    glBufferData(
      GL_ARRAY_BUFFER, 
      size * sizeof(glm::vec3), 
      value_ptr(vertices[0]), 
      typeDraw); //Put information into buffer
  }
  void Bind(unsigned int type = GL_ARRAY_BUFFER){
    glBindBuffer(type, address);
  }
  unsigned int size;
  unsigned int address;
};

class VertexArray {
public:
  VertexArray(std::vector<VertexBuffer*> buffers){
    glGenVertexArrays(1, &address);
    glBindVertexArray(address);
    m_VertexCount = buffers[0]->size;
    for(unsigned int index = 0;index < buffers.size(); index++){
      buffers[index]->Bind();
      
      glVertexAttribPointer(
        index, //Id of buffer to give data about
        3, //Size of each vertex (how many dimensions)
        GL_FLOAT, //Type of vertex data (needs to be gl constant)
        GL_FALSE,
        0, //stride (for interpolation of data)
        NULL); //Other specifications
      
      glEnableVertexAttribArray(index);
    }
  }
  
  void draw(unsigned int drawMode = GL_TRIANGLES){
    //glUseProgram(*m_Shader);
    glBindVertexArray(address);
    glDrawArrays(drawMode, 0, m_VertexCount);
  }
  
  unsigned int address;
private:
  unsigned int m_VertexCount = 0; //Set in addVBO function
};