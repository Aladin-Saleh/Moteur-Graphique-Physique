#include "allEngineFonction.h"

allEngineFonction * allEngineFonction::p_aef = nullptr;

allEngineFonction::allEngineFonction()
{
	p_aef = this;
}

void allEngineFonction::setFonction(ptrF f)
{
	allEngineFonction::p_fonction = f;
}

int allEngineFonction::foo(char * arg)
{
	return (*(p_aef->p_fonction.foo))(arg);
}