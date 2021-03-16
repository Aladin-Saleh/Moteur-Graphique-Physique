#ifdef _WIN32 
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include "FindClass.hpp"
#include <vector> 

namespace fs = std::filesystem;
void RecurseAdd(std::filesystem::path path);
void commandeSystem(char * c);
#endif
int main(int argc, char * argv[])
{
	#ifdef _WIN32 
	std::string path;
	char * commande;
	std::vector<std::string> pathOFile;
	int countOFileL = 0;

	if(argc < 2)
	{
		path = "./";
	}
	else
	{
		path = argv[1];
	}
	commandeSystem("rm -rf temp");
	commandeSystem("mkdir temp");
	for (const auto & entry : fs::directory_iterator(path + "Header"))
	{
		if (FindClass::isClassHpp(entry.path()))
		{
			std::string t = entry.path().u8string();
			commande = (char *)malloc(t.size() + 11);
			strcpy(commande, "cp ");
			strcat(commande, t.c_str());
			strcat(commande, " ./temp");
			commandeSystem(commande);
			free(commande);
		}
	}
	for (const auto & entry : fs::directory_iterator(path + "Source"))
	{
		if (FindClass::isClassCpp(entry.path()))
		{
			std::string t = entry.path().u8string();
			commande = (char *)malloc(t.size() + 11);
			strcpy(commande, "cp ");
			strcat(commande, t.c_str());
			strcat(commande, " ./temp");
			commandeSystem(commande);
			free(commande);
		}
	}
	RecurseAdd(path+ "Scene");
	RecurseAdd(path + "Script");
	RecurseAdd("../CAPS/Header/InterfaceDll");
	RecurseAdd("../CAPS/Header/Struct");
	RecurseAdd("../CAPS/Source/Struct");
	//exit(0);
	commandeSystem("g++ -std=c++1z -c ./temp/*.cpp -export-dynamic");
	commandeSystem("mv *.o ./temp");
	for (const auto & entry : fs::directory_iterator("./temp"))
	{
		if (FindClass::isOFile(entry.path()))
		{
			std::string t = entry.path().u8string();
			pathOFile.push_back(t);
			countOFileL += t.size() + 1;
		}
	}

	commande = (char *)malloc(countOFileL + 200);
#ifdef _WIN32 
	strcpy(commande, "g++ -std=c++1z -o CAPSDLL_Debug.dll -s -shared ");
#else
	strcpy(commande, "g++ -std=c++1z -fPIC -shared ");
#endif	
	for (int i = 0 ; i < pathOFile.size();i++)
	{
		strcat(commande, pathOFile[i].c_str());
		strcat(commande, " ");
	}
#ifdef _WIN32 
	strcat(commande, " -Wl,--subsystem,windows,--enable-stdcall-fixup CAPSDLL_Debug.def");
#else
	strcat(commande, " -o CAPSDLL_Debug.so -export-dynamic");
#endif	
	commandeSystem(commande);
	//std::cout << commande << std::endl;
	free(commande);
	commandeSystem("rm -rf temp");
	return 0;
	#endif
}
#ifdef _WIN32 
void commandeSystem(char * c)
{
	if (system(c) == -1)
	{
		std::cout << "Erreur :" << c << std::endl;
		exit(-1);
	}
}

void RecurseAdd(std::filesystem::path path)
{
	char * commande;
	for (const auto & entry : fs::directory_iterator(path))
	{
		std::cout << entry.path() << std::endl;
		if (FindClass::isClassFolder(entry.path()))
		{
			RecurseAdd(entry.path());
		}
		else if (FindClass::isClassHpp(entry.path()))
		{
			std::string t = entry.path().u8string();
			commande = (char *)malloc(t.size() + 11);
			strcpy(commande, "cp ");
			strcat(commande, t.c_str());
			strcat(commande, " ./temp");
			commandeSystem(commande);
			free(commande);
		}
		else if (FindClass::isClassCpp(entry.path()))
		{
			std::string t = entry.path().u8string();
			commande = (char *)malloc(t.size() + 11);
			strcpy(commande, "cp ");
			strcat(commande, t.c_str());
			strcat(commande, " ./temp");
			commandeSystem(commande);
			free(commande);
		}
	}
}
#endif