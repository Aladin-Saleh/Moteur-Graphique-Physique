#ifndef __ENGINE_FONCTION__
#define __ENGINE_FONCTION__

#include <dlfcn.h>
#include <iostream>
#include "testStatic.hpp"

struct ptrF 
{
	Ptrfoo foo = nullptr;
};

class allEngineFonction
{
public:
	allEngineFonction();
	void setFonction(ptrF f);
	static int foo(char * arg);
private:
	ptrF p_fonction;
	static allEngineFonction * p_aef;
};

#endif