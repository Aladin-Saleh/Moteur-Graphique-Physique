#include "FindClass.hpp"
#ifdef _WIN32 
bool FindClass::isClassCpp(std::filesystem::path path)
{
	std::string p = path.u8string();
	return p.substr(p.find_last_of(".") + 1) == "cpp";
}

bool FindClass::isClassHpp(std::filesystem::path path)
{
	std::string p = path.u8string();
	return p.substr(p.find_last_of(".") + 1) == "hpp";
}

bool FindClass::isOFile(std::filesystem::path path)
{
	std::string p = path.u8string();
	return p.substr(p.find_last_of(".") + 1) == "o";
}

bool FindClass::isClassFolder(std::filesystem::path path)
{
	fs::directory_entry folder(path);
	return folder.is_directory();
}
#endif