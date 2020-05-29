#include "VertexArray.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

VertexArray::VertexArray(const std::vector<std::shared_ptr<Buffer>>& buffers, const std::shared_ptr<Buffer>& indexBuffer)
: Buffers(buffers), IndexBuffer(indexBuffer) {
	GenVertexArrays();
	Configure();
}
VertexArray::VertexArray() {
	GenVertexArrays();
}
VertexArray::~VertexArray() {
	DeleteVertexArrays();
}
void VertexArray::Bind() const {
	glBindVertexArray(m_Address);
}
void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
// Generate vertex array TODO: multiple vertexaray generation
void VertexArray::GenVertexArrays() {
	glGenVertexArrays(1, &m_Address); 
}
// Delete array
void VertexArray::DeleteVertexArrays() {
	glDeleteVertexArrays(1, &m_Address);
}

// Reset vertex array to generated state, basically just undos Configure()
void VertexArray::Reset() {
	Bind();
	for(int i = 0; i < m_Attributes.size(); i++){
		glDisableVertexAttribArray(i);
	}
	Unbind();
	m_Attributes.clear();
	Loaded = false;
}
// Remove access to shared/unique buffers and Reset()
void VertexArray::Clear() {
	Reset();
	Buffers.clear();
	InstanceBuffer = NULL;
	IndexBuffer = NULL;
}

// Registers all elements of a buffer into vertexarray (to use the configuration, buffer shared_ptr must be in Buffers vector)
void VertexArray::RegisterAttribute(const Buffer* buffer, unsigned int elementIndex, bool isInstanceBuffer) {
	const BufferElement &element = buffer->GetLayout().GetElements()[elementIndex];
	buffer->Bind();
	
	unsigned int repeat = 1;
	unsigned int elemDimension = GetShaderTypeDimension(element.Type);
	if(elemDimension > 4){
		switch(element.Type){
		case ShaderType::Mat4:
			repeat = 4;
			break;
		case ShaderType::Mat3:
			repeat = 3;
			break;
		default:
			break;
		}
	}
	
	unsigned int baseDimension = elemDimension / repeat;
	unsigned int index;
	// Anything larger then vec4 has to be sent in multiples of vec4
	// e.g. mat4 has to be sent as 4 vec4s
	for(unsigned int i = 0; i < repeat; i++){
		index = m_Attributes.size();
		m_Attributes.push_back(element);
		//increase offset each time
		m_Attributes[index].Offset = ( i * (baseDimension) * sizeof(float) );
		glEnableVertexAttribArray(index);
			glVertexAttribPointer(
			index,
			baseDimension, // amount of element.Type in object (vec4 would be 4)
			GetShaderTypeNativeType(element.Type), // Send type, (GL_FLOAT OR GL_INT)
			element.Normalized, // Is is normalized?
			buffer->GetLayout().GetStride(), // Stride of all elements (how many bytes to get to next repeat of elements)
			(void*) (m_Attributes[index].Offset) // Offset for sending elements larger than vec4
		);
		
		// If is an instance buffer, need to set the sending divisor
		if(isInstanceBuffer){
			glVertexAttribDivisor(index, 1); 
		}
	}
	
	buffer->Unbind();
}
// Go through all the buffers and add all the buffer's elements to a list + configure into opengl
void VertexArray::Configure() {
  if(Loaded){Reset();}
  Bind();
  for(std::shared_ptr<Buffer>& buffer : Buffers){
    for(unsigned int i = 0;i < buffer->GetLayout().GetElements().size();i++){
      RegisterAttribute(buffer.get(), i);
    }
  }
  if(IndexBuffer != NULL){
    m_IndexCount = IndexBuffer->GetSize() / sizeof(unsigned int);
  }
  if(InstanceBuffer != NULL){
    m_InstanceCount = InstanceBuffer->GetSize() / InstanceBuffer->GetLayout().GetElements()[0].Size;
    RegisterAttribute(InstanceBuffer.get(), 0, true);
  }
  
  Loaded = true;
  Unbind();
}
// Draw configured vertex array to currently bound buffer
void VertexArray::Draw(unsigned int drawMode) const {
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

const std::vector<BufferElement>& VertexArray::GetAttributes() const {
  return m_Attributes;
}
