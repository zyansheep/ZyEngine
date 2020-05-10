#include "VertexArray.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

VertexArray::VertexArray(std::vector<Buffer*> buffers, Buffer* indexBuffer)
:VertexArray(){
  Buffers = buffers;
  IndexBuffer = indexBuffer;
  Configure();
}
VertexArray::VertexArray(){ glGenVertexArrays(1, &m_Address); }
VertexArray::~VertexArray(){
  glDeleteVertexArrays(1, &m_Address);
}
void VertexArray::Bind(){ glBindVertexArray(m_Address); }
void VertexArray::Unbind(){ glBindVertexArray(0); }
void VertexArray::Reset(){
  glDeleteVertexArrays(1, &m_Address);
  Loaded = false;
  m_Attributes.clear();
  glGenVertexArrays(1, &m_Address);
}
void VertexArray::Clear(){
  Reset();
  Buffers.clear();
  InstanceBuffer = NULL;
  IndexBuffer = NULL;
}
void VertexArray::ClearUnalloc(){
  for(Buffer* buffer : Buffers){
    delete buffer;
  }
  delete InstanceBuffer;
  delete IndexBuffer;
  Clear();
}

void VertexArray::RegisterAttribute(Buffer* buffer, unsigned int elementIndex, bool isInstanceBuffer){
  const BufferElement &element = buffer->GetLayout().GetElements()[elementIndex];
  buffer->Bind();
  
  unsigned int repeat = 1;
  unsigned int elemDimension = GetShaderTypeDimension(element.Type);
  if(elemDimension > 4){
    switch(element.Type){
      case ShaderType::Mat4:
        repeat = 4; break;
      case ShaderType::Mat3:
        repeat = 3; break;
      default: break;
    }
  }
  
  unsigned int baseDimension = elemDimension / repeat;
  unsigned int index;
  //Anything larger then vec4 has to be sent in multiples of vec4
  //e.g. mat4 has to be sent as 4 vec4s
  for(unsigned int i=0;i<repeat;i++){
    index = m_Attributes.size();
    m_Attributes.push_back(element);
    //increase offset each time
    m_Attributes[index].Offset = ( i * (baseDimension) * sizeof(float) );
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
      index,
      baseDimension, //amount of element.Type in object (vec4 would be 4)
      GetShaderTypeNativeType(element.Type), //Send type, (GL_FLOAT OR GL_INT)
      element.Normalized, //Is is normalized?
      buffer->GetLayout().GetStride(), //Stride of all elements (how many bytes to get to next repeat of elements)
      (void*) (m_Attributes[index].Offset) //Offset for sending elements larger than vec4
    );
    
    if(isInstanceBuffer){
      glVertexAttribDivisor(index, 1); 
    }
  }
  
  buffer->Unbind();
}
void VertexArray::Configure(){
  if(Loaded){Reset();}
  Bind();
  for(Buffer* buffer : Buffers){
    for(unsigned int i = 0;i < buffer->GetLayout().GetElements().size();i++){
      RegisterAttribute(buffer, i);
    }
  }
  if(IndexBuffer != NULL){
    m_IndexCount = IndexBuffer->GetSize() / sizeof(unsigned int);
  }
  if(InstanceBuffer != NULL){
    m_InstanceCount = InstanceBuffer->GetSize() / InstanceBuffer->GetLayout().GetElements()[0].Size;
    RegisterAttribute(InstanceBuffer, 0, true);
  }
  
  Loaded = true;
  Unbind();
}
void VertexArray::Draw(unsigned int drawMode){
  Bind();
  if(IndexBuffer != NULL){
    IndexBuffer->Bind();
    if(InstanceBuffer != NULL){
      glDrawElementsInstanced(drawMode, m_IndexCount, GL_UNSIGNED_INT, NULL, m_InstanceCount);
    }else{
      glDrawElements(drawMode, m_IndexCount, GL_UNSIGNED_INT, NULL);
    }
  }else{
    if(InstanceBuffer != NULL){
      glDrawArraysInstanced(drawMode, 0, m_VertexCount, m_InstanceCount);
    }else{
      glDrawArrays(drawMode, 0, m_VertexCount);
    }
  }
  Unbind();
}

std::vector<BufferElement> VertexArray::GetAttributes(){
  return m_Attributes;
}
