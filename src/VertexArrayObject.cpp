#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "Objects.cpp"

template<size_t NumVBOs>
class VertexArrayObject {
public:
  VertexArrayObject(){
    glGenVertexArrays(1, &m_VAO);
  }
  
  template<typename VertexType, size_t VertexDimensions>
  void addVBO(std::vector<Vertex<VertexType, VertexDimensions>> attributes){
    addVBO(attributes, m_NumVBOsAlloc);
  }
    
  template<typename VertexType, size_t VertexDimensions>
  void addVBO(std::vector<Vertex<VertexType, VertexDimensions>> attributes, 
  unsigned int attribIndex, 
  unsigned int typeDraw = GL_DYNAMIC_DRAW){
    glBindVertexArray(m_VAO); //Make current attribute collection to use
    //C array of the data
    VertexType* attributes_array = &(attributes[0].data[0]); //C array of the vector object
    
    glGenBuffers(1, &m_VBOs[attribIndex]); //gen new buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[attribIndex]); //designate current buffer
    glBufferData(
      GL_ARRAY_BUFFER, 
      attributes.size() * sizeof(Vertex<VertexType, VertexDimensions>), 
      attributes_array, 
      typeDraw); //Put information into buffer
    
    //T type;
    glVertexAttribPointer(
      attribIndex, //Id of buffer to give data about
      VertexDimensions, //Size of each vertex (how many dimensions)
      GL_FLOAT, //Type of vertex data (needs to be gl constant)
      GL_FALSE,
      0, //stride (for interpolation of data)
      NULL); //Other specifications
    
    glEnableVertexAttribArray(attribIndex);
    
    m_NumVBOsAlloc++;
  }
  
  template<typename VertexType, size_t VertexDimensions>
  void modifyVBO(unsigned int attribIndex, 
  std::vector<Vertex<VertexType, VertexDimensions>> attributes){
    
  }
  void setShader(unsigned int &shader){
    m_Shader = &shader;
  }
  
  void draw(unsigned int drawMode = GL_TRIANGLES){
    glUseProgram(*m_Shader);
    glBindVertexArray(m_VAO);
    glDrawArrays(drawMode, 0, m_VertexCount);
  }
  
  unsigned int m_VAO;
  unsigned int m_VBOs[NumVBOs];
  unsigned int *m_Shader;

private:
  unsigned int m_VertexCount = 3; //min indices: 3
  unsigned int m_NumVBOsAlloc = 0;
};