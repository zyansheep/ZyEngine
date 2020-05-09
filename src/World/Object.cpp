#include "Object.h"

Object::Object(VertexArray* vertexArray, Shader& shader, std::string modelUniform)
: m_VertexArray(vertexArray), m_Shader(shader){
  m_MatrixLocation = shader.GetUniformLocation(modelUniform.c_str());
}
Object::Object(VertexArray* vertexArray, Shader& shader, std::vector<std::shared_ptr<Texture>> textures, std::string modelUniform)
: m_VertexArray(vertexArray), m_Shader(shader), m_Textures(textures){
  m_MatrixLocation = shader.GetUniformLocation(modelUniform.c_str());
}
Object::~Object(){
  m_VertexArray->ClearUnalloc();
}

void Object::Render(Camera& viewport){
  //Check if MatrixArray size differs from internal calculated MVPVec
  if(m_MVPVec.size() != MatrixArray.size()){ m_MVPVec = MatrixArray; }
  for(unsigned int i=0;i<MatrixArray.size();i++){ m_MVPVec[i] = viewport.matrix * MatrixArray[i]; } //create MVP matricies
  if(MatrixArray.size() > 1){
    //Object is allowed to modify Instance Buffer
    Buffer* buffer = m_VertexArray->InstanceBuffer;
    if(buffer == NULL){
      m_VertexArray->InstanceBuffer = new Buffer({{ShaderType::Mat4, "a_transform"}});
      m_VertexArray->Configure(); //configure buffer after set it
      buffer = m_VertexArray->InstanceBuffer;
      std::cout << "Printing Attributes" << '\n';
      auto elems = m_VertexArray->GetAttributes();
      for(unsigned int i=0;i<elems.size();i++){
        std::cout << "Index: "<<i<<" name: "<<elems[i].Name << " offset: "<<elems[i].Offset<<'\n';
      }
    }
    if(m_MVPVec.size() * sizeof(m_MVPVec[0]) != buffer->GetSize()){
      buffer->New(&m_MVPVec[0], m_MVPVec.size() * sizeof(m_MVPVec[0])); //set buffer to tempvec
      m_VertexArray->Configure();
    }else{
      buffer->Modify(&m_MVPVec[0], sizeof(m_MVPVec[0]) * m_MVPVec.size());
    }
  }else{
    m_MVP = m_MVPVec[0];
  }
}
void Object::Draw(){
  for(auto& texture : m_Textures){
    texture->Bind();
  }
  //m_Shader.Uniform(m_Shader.GetUniformLocation(viewport->Properties.UniformName.c_str()), viewport->matrix);
  m_Shader.Bind();
  if(m_VertexArray->InstanceBuffer == NULL){
    m_Shader.Uniform(m_MatrixLocation, m_MVP);
  }
  m_VertexArray->Draw();
}

void Object::Rotate(float degrees, glm::vec3 axis, unsigned int index){
  MatrixArray[index] = glm::rotate(MatrixArray[index], glm::radians(degrees), axis);
}
void Object::Translate(glm::vec3 v, unsigned int index){
  MatrixArray[index] = glm::translate(MatrixArray[index], v);
}
void Object::Scale(glm::vec3 factor, unsigned int index){
  MatrixArray[index] = glm::scale(MatrixArray[index], factor);
}