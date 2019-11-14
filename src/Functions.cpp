#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "glad/glad.h"
#include "Objects.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static void printGlError(std::string str){
  std::cout << glGetError() << "-" << str << '\n';
}

static std::string readFileSync(std::string file_path){
  // Read the Vertex Shader code from the file
	std::string Data;
	std::ifstream DataStream(file_path, std::ios::in);
	if(DataStream.is_open()){
		std::stringstream sstr;
		sstr << DataStream.rdbuf();
		Data = sstr.str();
		DataStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory?\n", file_path.c_str());
	}
  return Data;
}
