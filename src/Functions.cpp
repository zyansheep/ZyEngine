#include <iostream>
#include <string>
#include "glad/glad.h"

static void printGlError(std::string str){
  std::cout << glGetError() << "-" << str << '\n';
}