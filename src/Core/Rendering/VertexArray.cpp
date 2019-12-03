#include "VertexArray.h"

void VertexArray::Bind(){
  glBindVertexArray(m_Address);
}
void VertexArray::AddVertexBuffer(Buffer* buffer){
  
  
  const std::vector<BufferElement>& elements = buffer->GetLayout().GetElements();
  const BufferElement& element0 = elements[0];
  m_VertexCount = buffer->GetSize() / elements[0].Size;
  for (uint32_t index = 0; index < elements.size(); index++){
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(
          index,
          GetShaderTypeDimension(elements[index].Type),
          GetShaderTypeNativeType(elements[index].Type),
          elements[index].Normalized,
          buffer->GetLayout().GetStride(),
          (const void*) elements[index].Offset
      );
  }
  m_VertexBuffers.push_back(buffer);
}
void VertexArray::SetIndexBuffer(Buffer* buffer){
  m_IndexBuffer = buffer;
  m_IndexCount = m_IndexBuffer->GetSize() / sizeof(unsigned int);
}
void VertexArray::Draw(unsigned int drawMode){
  glBindVertexArray(m_Address);
  if(m_IndexBuffer != NULL){
    glDrawElements(drawMode, m_IndexCount, GL_UNSIGNED_INT, NULL);
  }else{
    glDrawArrays(drawMode, 0, m_VertexCount);
  }
  
}