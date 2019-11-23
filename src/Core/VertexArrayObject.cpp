#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "Shader.cpp"

class VertexBufferObject {
public:
  VertexBufferObject(std::vector<glm::vec3> vertices, unsigned int typeDraw = GL_STATIC_DRAW)
  : vertices(vertices){
    
    glGenBuffers(1, &address); //gen new buffer
    glBindBuffer(GL_ARRAY_BUFFER, address); //designate current buffer
    glBufferData(
      GL_ARRAY_BUFFER, 
      vertices.size() * sizeof(vertices[0]), 
      &vertices[0], 
      typeDraw); //Put information into buffer
  }
  std::vector<glm::vec3> vertices;
  unsigned int address;
};

class VertexArrayObject {
public:
  VertexArrayObject(std::vector<VertexBufferObject> attributes){
    glGenVertexArrays(1, &m_VAO);
    
    glBindVertexArray(m_VAO); //Make current attribute collection to use
    for(unsigned int i = 0; i < attributes.size();i++){
      glBindBuffer(GL_ARRAY_BUFFER, attributes[i].address);
      //T type;
      glVertexAttribPointer(
        attributes[i].address, //Id of buffer to give data about
        sizeof(attributes[i].vertices) / sizeof(float), //Size of each vertex (how many dimensions)
        GL_FLOAT, //Type of vertex data (needs to be gl constant)
        GL_FALSE,
        0, //stride (for interpolation of data)
        NULL); //Other specifications
      
      glEnableVertexAttribArray(i);
    }
  }
  
  template<typename VertexType, size_t VertexDimensions>
  void modifyVBO(unsigned int attribIndex, 
  std::vector<glm::vec<VertexDimensions, VertexType>> attributes){
    
  }
  
  void draw(unsigned int drawMode = GL_TRIANGLES){
    glBindVertexArray(m_VAO);
    glDrawArrays(drawMode, 0, m_VertexCount);
  }
  
  unsigned int m_VAO;

private:
  signed int m_VertexCount = 0; //Set in addVBO function
  unsigned int m_NumVBOsAlloc = 0;
};