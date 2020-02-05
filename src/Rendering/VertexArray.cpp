#include "VertexArray.h"

void VertexArray::RegisterAttribute(Buffer* buffer, uint elementIndex, bool isInstanceBuffer){
  const BufferElement &element = buffer->GetLayout().GetElements()[elementIndex];
  buffer->Bind();
  
  uint repeat = 1;
  uint elemDimension = GetShaderTypeDimension(element.Type);
  if(elemDimension > 4){
    switch(element.Type){
      case ShaderType::Mat4:
        repeat = 4; break;
      case ShaderType::Mat3:
        repeat = 3; break;
      default: break;
    }
  }
  
  uint baseDimension = elemDimension / repeat;
  uint index;
  //Anything larger then vec4 has to be sent in multiples of vec4
  //e.g. mat4 has to be sent as 4 vec4s
  for(uint i=0;i<repeat;i++){
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
    for(uint i = 0;i < buffer->GetLayout().GetElements().size();i++){
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
