#ifndef __CAPS_SCENE__
#define __CAPS_SCENE__

#include "EngineFonction.hpp"

class Scene
{
public:
	virtual void Load() = 0;//full virtual

	virtual void UnLoad() = 0;
};

#endif //__CAPS_SCENE__