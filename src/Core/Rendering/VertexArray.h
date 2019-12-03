#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Buffer.h"

class VertexArray {
public:
  VertexArray(std::vector<Buffer*> vertexBuffers, Buffer* indexBuffer = NULL)
  :VertexArray(){
    for(Buffer* buff : vertexBuffers){
      AddVertexBuffer(buff);
    }
    if(indexBuffer != NULL){
      SetIndexBuffer(indexBuffer);
    }
  }
  VertexArray(){
    glGenVertexArrays(1, &m_Address);
    glBindVertexArray(m_Address);
  }
  ~VertexArray(){
    glDeleteVertexArrays(1, &m_Address);
  }
  void Bind();
  void AddVertexBuffer(Buffer* buffer);
  void SetIndexBuffer(Buffer* buffer);
  
  void Draw(unsigned int drawMode = GL_TRIANGLES);
private:
  std::vector<Buffer*> m_VertexBuffers;
  unsigned int m_VertexCount;
  
  Buffer* m_IndexBuffer;
  unsigned int m_IndexCount;
  
  unsigned int m_Address;
};