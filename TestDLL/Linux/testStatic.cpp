#include "testStatic.hpp"

TestStatic * TestStatic::p_Test = nullptr;

void TestStatic::Initialize()
{
	p_Test = this;
}

int TestStatic::foo(char * arg)
{
	printf("%s\n",arg);
	return 50;
}