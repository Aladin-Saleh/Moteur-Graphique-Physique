#include <dlfcn.h>
#include <iostream>
#include "myclass.h"
#include "allEngineFonction.h"
#include "testStatic.hpp"

int main(int argc, char **argv)
{
	void* handle = dlopen("./myclass.so", RTLD_LAZY);

	TestStatic t;
	t.Initialize();

	char cstr[4];
	cstr[0] = 'e';
	cstr[1] = 'x';
	cstr[2] = 'e';
	cstr[3] = '\0';
	TestStatic::foo(cstr);

	if(handle == nullptr)
	{
		std::cout << "So non trouvé" << std::endl;
		handle = dlopen("./myclass.dll", RTLD_LAZY);
		if(handle == nullptr)
		{
			std::cout << "dll non trouvé" << std::endl;
			return 0;
		}
	}

	MyClass* (*create)();
	void(*destroy)(MyClass*);

	create = (MyClass* (*)())dlsym(handle, "create_object");
	destroy = (void(*)(MyClass*))dlsym(handle, "destroy_object");

	ptrF allptr;
	allptr.foo = &TestStatic::foo;

	MyClass* myClass = (MyClass*)create();
	myClass->setFonction(allptr);
	myClass->DoSomething();

	destroy(myClass);
	return 0;
}