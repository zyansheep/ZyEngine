#pragma once

#include <vector>
#include <string>
#include <initializer_list>

#include "ShaderType.h"

#include <glad/glad.h>

struct BufferElement {
  ShaderType Type;
  std::string Name;
  unsigned int Size;
  size_t Offset;
  bool Normalized;

  BufferElement() {}
  BufferElement(ShaderType type, const std::string& name, bool normalized = false)
  : Type(type), Name(name), Size(GetShaderTypeSize(type)), Offset(0), Normalized(normalized) {}
};
class BufferLayout{
public:
  BufferLayout() {}
  BufferLayout(std::initializer_list<BufferElement> elements);
  
  const std::vector<BufferElement>& GetElements() const { return m_Elements; }
  unsigned int GetStride() const { return m_Stride; }
  unsigned int GetTypeDraw() const { return m_TypeDraw; }
  unsigned int GetTypeBuffer() const { return m_TypeBuffer; }
  void SetTypeBuffer(unsigned int typeBuffer) {m_TypeBuffer = typeBuffer;}
private:
  std::vector<BufferElement> m_Elements; //Number of *different* element types eg Float4, Mat3 in buffer
  unsigned int m_Stride = 0; //Size of each index of elements eg sizeof(Float4) + sizeof(Mat3)
  unsigned int m_TypeDraw = GL_STATIC_DRAW; //Whether the buffer data will be changing over time
  unsigned int m_TypeBuffer = GL_ARRAY_BUFFER; //What kind of buffer is it?
};

class Buffer {
public:
  Buffer();
  Buffer(BufferLayout layout);
  ~Buffer();
  void Bind();
  void Unbind();
  void New(void* data, size_t size);
  template<typename Unknown>
  void New(std::vector<Unknown> &data);
  void Modify(void* data, size_t size, size_t offset = 0);
  template<typename Unknown>
  void Modify(std::vector<Unknown> &data, size_t offset = 0);
  
  BufferLayout& GetLayout(){ return m_Layout; }
  unsigned int GetSize(){ return m_Size; }
private:
  BufferLayout m_Layout;
  unsigned int m_Address;
  unsigned int m_Size;
};
