#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Buffer.h"

#pragma once

class VertexArray {
public:
  VertexArray(std::vector<Buffer*> buffers, Buffer* indexBuffer = NULL)
  :VertexArray(){
    Buffers = buffers;
    IndexBuffer = indexBuffer;
    Configure();
  }
  VertexArray(){ glGenVertexArrays(1, &m_Address); }
  ~VertexArray(){
    glDeleteVertexArrays(1, &m_Address);
  }
  
  void Bind(){ glBindVertexArray(m_Address); }
  void Unbind(){ glBindVertexArray(0); }
  
  void Reset(){
    glDeleteVertexArrays(1, &m_Address);
    Loaded = false;
    m_Attributes.clear();
    glGenVertexArrays(1, &m_Address);
  }
  //Clear all linked buffers and reset Object
  void Clear(){
    Reset();
    Buffers.clear();
    InstanceBuffer = NULL;
    IndexBuffer = NULL;
  }
  //Deallocate items before Clearing
  void ClearUnalloc(){
    for(Buffer* buffer : Buffers){
      delete buffer;
    }
    delete InstanceBuffer;
    delete IndexBuffer;
    Clear();
  }
  
  void RegisterAttribute(Buffer* buffer, unsigned int elementIndex, bool isInstanceBuffer = false); //Register Buffer* into opengl VAO
  void Configure(); //function called to configure all set buffers into vertexarray
  void Draw(unsigned int drawMode = GL_TRIANGLES); //call gl draw function depending set buffers
  std::vector<BufferElement> GetAttributes(){
    return m_Attributes;
  }
  
  bool Loaded = false;
  std::vector<Buffer*> Buffers;
  Buffer* InstanceBuffer = NULL;
  Buffer* IndexBuffer = NULL;
private:
  std::vector<BufferElement> m_Attributes;
  unsigned int m_VertexCount = 0; //For Array Drawing
  unsigned int m_IndexCount = 0; //For Element Drawing
  unsigned int m_InstanceCount = 0; //For Instance Drawing
  
  unsigned int m_Address;
};
