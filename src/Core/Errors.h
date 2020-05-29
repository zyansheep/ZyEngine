#pragma once

#include "glad/glad.h"

#define ZY_DEBUG DEBUG

#ifndef ZY_OPTIMIZED
	#ifdef ZY_DEBUG
		#include <assert.h>
		inline void ZY_GL_ERROR(const std::string& str){
			unsigned int err = glGetError();
			if(err != GL_NO_ERROR) {
				printf("error: gl: %d: %s\n", err, str.c_str());
				assert(err != GL_NO_ERROR);
			}
		}
	#else
		inline void ZY_GL_ERROR(const std::string& str){
			unsigned int err = glGetError();
			if(err != GL_NO_ERROR){
				prinf("error: gl: %d: %s\n", err, str.c_str());
			}
		}
	#endif
#else
	inline void ZY_GL_ERROR(const std::sttring& str){}
#endif

