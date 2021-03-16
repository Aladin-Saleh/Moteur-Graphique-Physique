#include "myclass.h"

extern "C" MyClass* create_object()
{
	return new MyClass;
}

extern "C" void destroy_object(MyClass* object)
{
	delete object;
}

MyClass::MyClass()
{
	x = 50;
}

void MyClass::setFonction(ptrF f)
{
	MyClass::aef.setFonction(f);
}

void MyClass::DoSomething()
{
	std::cout << x << std::endl;
	char cstr[4];
	cstr[0] = 'c';
	cstr[1] = 'a';
	cstr[2] = 'l';
	cstr[3] = '\0';
	std::cout << allEngineFonction::foo(cstr) << std::endl;
	for (int i = 0; i < 10; i++)
	{
		allEngineFonction::foo(cstr);
	}
}