#include "Utils.h"

//using namespace utils

#include <iostream>

#include <fstream>
#include <sstream>

std::string Utils::ReadFileSync(const std::string& file_path){
	// Read the Vertex Shader code from the file
	std::string Data;
	std::ifstream DataStream(file_path, std::ios::in);
	if(DataStream.is_open()){
		std::stringstream sstr;
		sstr << DataStream.rdbuf();
		Data = sstr.str();
		DataStream.close();
	} else {
		/*char resolved_path[PATH_MAX]; 
		realpath(file_path.c_str(), resolved_path); 
		printf("\n%s\n",resolved_path);*/
		printf("[ZyEngine][error] Impossible to open %s. Are you in the right directory?\n", file_path.c_str());
	}
	return Data;
}

#include "Preprocessor.h"
#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef ZY_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::string Utils::GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}