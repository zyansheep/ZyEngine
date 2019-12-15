#include "VertexArray.h"

void VertexArray::Bind(){
  glBindVertexArray(m_Address);
}
void VertexArray::AddVertexBuffer(Buffer* buffer){
  const std::vector<BufferElement>& elements = buffer->GetLayout().GetElements();
  //m_VertexCount = buffer->GetSize() / elements[0].Size;
  buffer->Bind();
  auto* test = &elements[0];
  m_VertexCount = 36;
  for (unsigned int index = 0; index < elements.size(); index++){
    glEnableVertexAttribArray(m_AttribIndex);
    glVertexAttribPointer(
      m_AttribIndex,
      GetShaderTypeDimension(elements[index].Type),
      GetShaderTypeNativeType(elements[index].Type),
      elements[index].Normalized,
      buffer->GetLayout().GetStride(),
      (const void*) elements[index].Offset
    );
    m_AttribIndex++;
  }
  m_VertexBuffers.push_back(buffer);
}
void VertexArray::SetIndexBuffer(Buffer* buffer){
  m_IndexBuffer = buffer;
  m_IndexCount = m_IndexBuffer->GetSize() / sizeof(unsigned int);
  std::cout << "IndexCount: "<<m_IndexCount << '\n';
}
void VertexArray::Draw(unsigned int drawMode){
  glBindVertexArray(m_Address);
  if(m_IndexBuffer != NULL){
    glDrawElements(drawMode, m_IndexCount, GL_UNSIGNED_INT, NULL);
  }else{
    glDrawArrays(drawMode, 0, m_VertexCount);
  }
}
