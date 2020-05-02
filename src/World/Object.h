#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

#include "Rendering/VertexArray.h"
#include "Rendering/Shader.h"
#include "Camera.h"

#pragma once

class Object {
public:
  Object(VertexArray* vertexArray, Shader& shader, std::string modelUniform = "u_matrix")
  : m_VertexArray(vertexArray), m_Shader(shader){
    
    m_MatrixLocation = shader.GetUniformLocation(modelUniform.c_str());
  }
  ~Object(){m_VertexArray->ClearUnalloc();}
  void Render(Camera* viewport){
    if(m_MVPVec.size() != MatrixArray.size()){ m_MVPVec = MatrixArray; }
    for(unsigned int i=0;i<MatrixArray.size();i++){ m_MVPVec[i] = viewport->matrix * MatrixArray[i]; } //create MVP matricies
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
      //m_VertexArray->Bind();
      //This is very inefficient, creating a new buffer every frame
    
    }else{
      m_MVP = m_MVPVec[0];
    }
  }
  void Draw(){
    m_Shader.Bind();
    //m_Shader.Uniform(m_Shader.GetUniformLocation(viewport->Properties.UniformName.c_str()), viewport->matrix);
    if(m_VertexArray->InstanceBuffer == NULL){
      m_Shader.Uniform(m_MatrixLocation, m_MVP);
    }
    m_VertexArray->Draw();
  }
  
  void Rotate(float degrees, glm::vec3 axis, unsigned int index = 0){
    MatrixArray[index] = glm::rotate(MatrixArray[index], glm::radians(degrees), axis);
  }
  void Translate(glm::vec3 v, unsigned int index = 0){
    MatrixArray[index] = glm::translate(MatrixArray[index], v);
  }
  void Scale(glm::vec3 factor, unsigned int index = 0){
    MatrixArray[index] = glm::scale(MatrixArray[index], factor);
  }
  
  std::vector<glm::mat4> MatrixArray = {glm::mat4(1.0f)}; //Positions of object (if greater than 1, render() will generate InstanceBuffer)
protected:
  std::vector<glm::mat4> m_MVPVec = {glm::mat4(1.0f)};
  //Using Uniforms for single matrix, attributes for instanced rendering
  int m_MatrixLocation; //Uniform Location of Model Matrix
  glm::mat4 m_MVP;
  
  VertexArray* m_VertexArray; //NOT MANAGED BY Object.h
  Shader& m_Shader;
};
