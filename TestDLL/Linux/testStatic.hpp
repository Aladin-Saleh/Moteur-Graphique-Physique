#ifndef __TESTSTATIC_H__
#define __TESTSTATIC_H__

#include <iostream>

typedef int (*Ptrfoo)(char *);

class TestStatic
{
public:
	void Initialize();

	static int foo(char * arg);
private:
	static TestStatic * p_Test;
};

#endif