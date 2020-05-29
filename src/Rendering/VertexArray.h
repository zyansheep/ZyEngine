#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Buffer.h"

class VertexArray {
public:
  VertexArray(const std::vector<std::shared_ptr<Buffer>>& buffers, const std::shared_ptr<Buffer>& indexBuffer = NULL);
  VertexArray();

  ~VertexArray();
  
  void Bind() const;
  void Unbind() const;
  void GenVertexArrays();
  void DeleteVertexArrays();
  
  void Reset();
  void Clear();
  
  void RegisterAttribute(const Buffer* buffer, unsigned int elementIndex, bool isInstanceBuffer = false); //Register Buffer* into opengl VAO
  void Configure(); //function called to configure all set buffers into vertexarray
  void Draw(unsigned int drawMode = GL_TRIANGLES) const; //call gl draw function depending set buffers
  const std::vector<BufferElement>& GetAttributes() const;
  
  bool Loaded = false;
  std::vector<std::shared_ptr<Buffer>> Buffers; //Allow for shared buffers across vertexarrays
  std::shared_ptr<Buffer> IndexBuffer = NULL;
  std::unique_ptr<Buffer> InstanceBuffer = NULL;
private:
  std::vector<BufferElement> m_Attributes;
  unsigned int m_VertexCount = 0; //For Array Drawing
  unsigned int m_IndexCount = 0; //For Element Drawing
  unsigned int m_InstanceCount = 0; //For Instance Drawing
  
  unsigned int m_Address;
};
