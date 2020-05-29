#pragma once

#include <string>

namespace Utils {
	std::string ReadFileSync(const std::string& file_path);
	std::string GetCurrentWorkingDir();
};
