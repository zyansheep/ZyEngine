#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "glad/glad.h"
#include "Objects.cpp"



static void printGlError(std::string str){
  std::cout << glGetError() << "-" << str << '\n';
}


static void registerVAO(unsigned int &vao){
  glGenVertexArrays(1, &vao); //generate
}
/*static unsigned int* registerAttributeCollection(unsigned int size){
  unsigned int collectionIDArray[size];
  glGenVertexArrays(size, &collectionIDArray); //generate
  return *collectionIDArray;
}*/

template<typename T, size_t N>
static void registerVBO(unsigned int &vbo, unsigned int vao, unsigned int attribIndex, std::vector<Vertex<T, N>> attributes){
  glBindVertexArray(vao); //Make current attribute collection to use
  
  //C array of the data
  T* attributes_array = &(attributes[0].data[0]); //C array of the vector object
  
  glGenBuffers(1, &vbo); //gen new buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbo); //designate current buffer
  glBufferData(
    GL_ARRAY_BUFFER, 
    attributes.size() * sizeof(Vertex<T, N>), 
    attributes_array, 
    GL_STATIC_DRAW); //Put information into buffer
  
  
  //T type;
  glVertexAttribPointer(
    attribIndex, //Id of buffer to give data about
    N, //Size of each vertex (how many dimensions)
    GL_FLOAT, //Type of vertex data (needs to be gl constant)
    GL_FALSE,
    0, //stride (for interpolation of data)
    NULL); //Other specifications
  
  glEnableVertexAttribArray(attribIndex);
}
