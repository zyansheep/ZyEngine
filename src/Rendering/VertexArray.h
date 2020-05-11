#pragma once

#include <iostream>
#include <vector>

#include "Buffer.h"

class VertexArray {
public:
  VertexArray(std::vector<Buffer*> buffers, Buffer* indexBuffer = NULL);
  
  VertexArray();
  ~VertexArray();
  
  void Bind();
  void Unbind();
  
  void Reset();
  //Clear all linked buffers and reset Object
  void Clear();
  //Deallocate items before Clearing
  void ClearUnalloc();
  
  void RegisterAttribute(Buffer* buffer, unsigned int elementIndex, bool isInstanceBuffer = false); //Register Buffer* into opengl VAO
  void Configure(); //function called to configure all set buffers into vertexarray
  void Draw(unsigned int drawMode = GL_TRIANGLES); //call gl draw function depending set buffers
  std::vector<BufferElement> GetAttributes();
  
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
