#pragma once

#include <string>

#include <glad/glad.h>


enum class ShaderType {
  Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
};

static unsigned int GetShaderTypeSize(ShaderType type){
  switch (type){
    case ShaderType::Float:     return sizeof(float);
    case ShaderType::Float2:    return sizeof(float) * 2;
    case ShaderType::Float3:    return sizeof(float) * 3;
    case ShaderType::Float4:    return sizeof(float) * 4;
    case ShaderType::Int:       return sizeof(int);
    case ShaderType::Int2:      return sizeof(int) * 2;
    case ShaderType::Int3:      return sizeof(int) * 3;
    case ShaderType::Int4:      return sizeof(int) * 4;
    case ShaderType::Mat3:      return sizeof(float) * 3 * 3;
    case ShaderType::Mat4:      return sizeof(float) * 4 * 4;
    case ShaderType::Bool:      return sizeof(bool);
  }
  return 0;
}

static unsigned int GetShaderTypeDimension(ShaderType type){
  switch (type){
    case ShaderType::Float:     return 1;
    case ShaderType::Float2:    return 2;
    case ShaderType::Float3:    return 3;
    case ShaderType::Float4:    return 4;
    case ShaderType::Int:       return 1;
    case ShaderType::Int2:      return 2;
    case ShaderType::Int3:      return 3;
    case ShaderType::Int4:      return 4;
    case ShaderType::Mat3:      return 3 * 3;
    case ShaderType::Mat4:      return 4 * 4;
    case ShaderType::Bool:      return 1;
  }
  return 0;
}
static unsigned int GetShaderTypeNativeType(ShaderType type){
  switch (type){
    case ShaderType::Float:     return GL_FLOAT;
    case ShaderType::Float2:    return GL_FLOAT;
    case ShaderType::Float3:    return GL_FLOAT;
    case ShaderType::Float4:    return GL_FLOAT;
    case ShaderType::Int:       return GL_INT;
    case ShaderType::Int2:      return GL_INT;
    case ShaderType::Int3:      return GL_INT;
    case ShaderType::Int4:      return GL_INT;
    case ShaderType::Mat3:      return GL_FLOAT;
    case ShaderType::Mat4:      return GL_FLOAT;
    case ShaderType::Bool:      return GL_BOOL;
  }
  return 0;
}