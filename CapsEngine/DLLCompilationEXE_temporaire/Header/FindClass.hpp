#ifndef __CAPSDLL_COMPILATION_FIND_CLASS__
#define __CAPSDLL_COMPILATION_FIND_CLASS__
#ifdef _WIN32 
#include <iostream>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

class FindClass
{
public:
	static bool isClassCpp(std::filesystem::path path);
	static bool isClassHpp(std::filesystem::path path);
	static bool isOFile(std::filesystem::path path);
	static bool isClassFolder(std::filesystem::path path);
};
#endif
#endif //!__CAPSDLL_COMPILATION_FIND_CLASS__