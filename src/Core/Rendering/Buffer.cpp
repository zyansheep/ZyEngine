#include "Buffer.h"

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
: m_Elements(elements){
    size_t offset = 0;
    for (BufferElement& element : m_Elements){
        element.Offset = offset;
        offset += element.Size;
    }
    if(elements.size() > 1){
      m_Stride = offset;
    }
}

void Buffer::Bind(){
  glBindBuffer(m_Layout.GetTypeBuffer(), m_Address);
}
void Buffer::SetData(void* data, size_t size){
  m_RawSize = size;
  Bind();
  //Put information into buffer
  glBufferData(
    m_Layout.GetTypeBuffer(), 
    size, 
    data, 
    m_Layout.GetTypeDraw());
}