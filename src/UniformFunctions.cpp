//Primitives

#include "Objects.cpp"
#include "glad/glad.h"
void Uniform(unsigned int location, float toSend){
  glUniform1f(location, toSend);
}
void Uniform(unsigned int location, int toSend){
  glUniform1i(location, toSend);
}
void Uniform(unsigned int location, unsigned int toSend){
  glUniform1ui(location, toSend);
}

//Vectors length 2
void Uniform(unsigned int location, Vertex<float, 2> &toSend){
  glUniform2fv(location, 1, toSend.data);
}
void Uniform(unsigned int location, Vertex<int, 2> &toSend){
  glUniform2iv(location, 1, toSend.data);
}
void Uniform(unsigned int location, Vertex<unsigned int, 2> &toSend){
  glUniform2uiv(location, 1, toSend.data);
}

//Vectors length 3
void Uniform(unsigned int location, Vertex<float, 3> &toSend){
  glUniform3fv(location, 1, toSend.data);
}
void Uniform(unsigned int location, Vertex<int, 3> &toSend){
  glUniform3iv(location, 1, toSend.data);
}
void Uniform(unsigned int location, Vertex<unsigned int, 3> &toSend){
  glUniform3uiv(location, 1, toSend.data);
}

//Vectors length 4
void Uniform(unsigned int location, Vertex<float, 4> &toSend){
  glUniform4fv(location, 1, toSend.data);
}
void Uniform(unsigned int location, Vertex<int, 4> &toSend){
  glUniform4iv(location, 1, toSend.data);
}
void Uniform(unsigned int location, Vertex<unsigned int, 4> &toSend){
  glUniform4uiv(location, 1, toSend.data);
}

//Catch-All
/*
template<typename TypePrimitive>
void Uniform(unsigned int location, TypePrimitive toSend){
  if(std::is_same<TypePrimitive, float>::value){
    glUniform1f(location, toSend);
  }else if(std::is_same<TypePrimitive, int>::value){
    glUniform1i(location, toSend);
  }else if(std::is_same<TypePrimitive, unsigned int>::value){
    glUniform1ui(location, toSend);
  }
}
template<typename VectorPrimitive, size_t VectorSize>
void Uniform(unsigned int location, Vertex<VectorPrimitive, VectorSize> &toSend){
  if(std::is_same<VectorPrimitive, float>::value){
    glUniform1fv(location, VectorSize, (float*)(&toSend.data[0])  );
  }else if(std::is_same<VectorPrimitive, int>::value){
    glUniform1iv(location, VectorSize, (int*)(&toSend.data[0])  );
  }else if(std::is_same<VectorPrimitive, unsigned int>::value){
    glUniform1uiv(location, VectorSize, (unsigned int*)(&toSend.data[0])  );
  }
}
*/
