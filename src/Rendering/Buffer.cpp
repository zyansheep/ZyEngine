#include "Buffer.h"

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
: m_Elements(elements){
    size_t offset = 0;
    for (BufferElement& element : m_Elements){
        element.Offset = offset;
        offset += element.Size;
    }
    m_Stride = offset;
}

void Buffer::Bind(){
  glBindBuffer(m_Layout.GetTypeBuffer(), m_Address);
}
void Buffer::Unbind(){
  glBindBuffer(m_Layout.GetTypeBuffer(), 0);
}
void Buffer::New(void* data, size_t size){
  m_Size = size;
  Bind();
  //Put information into buffer
  glBufferData(
    m_Layout.GetTypeBuffer(), 
    m_Size, 
    data, 
    m_Layout.GetTypeDraw());
}
template <typename Unknown>
void Buffer::New(std::vector<Unknown> &data){
  SetData(&data[0], data.size() * sizeof(Unknown));
}
void Buffer::Modify(void* data, size_t size, size_t offset){
  if(m_Size >= size - offset){
    Bind();
    glBufferSubData( 
      m_Layout.GetTypeBuffer(),
      offset,
      size,
      data
    );
  }
}
template <typename Unknown>
void Buffer::Modify(std::vector<Unknown> &data, size_t offset){
  size_t size = sizeof(Unknown) * data.size();
  if(m_Size >= size - offset){
    Bind();
    glBufferSubData( 
      m_Layout.GetTypeBuffer(),
      offset,
      size,
      &data[0]
    );
  }
}
