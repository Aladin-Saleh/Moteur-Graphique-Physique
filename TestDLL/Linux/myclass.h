#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include <dlfcn.h>
#include <iostream>
#include "allEngineFonction.h"

class MyClass
{
public:
	MyClass();
	virtual void DoSomething();
	virtual void setFonction(ptrF f);
private:
	allEngineFonction aef;
	int x;
};

#endif