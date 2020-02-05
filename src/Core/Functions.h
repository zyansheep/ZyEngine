#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "Preprocessor.h"

#pragma once

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

#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef ZY_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
 
static std::string GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}
