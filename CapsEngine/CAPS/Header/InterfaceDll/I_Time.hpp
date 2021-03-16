#ifndef __CAPS_INTERFACE_TIME__
#define __CAPS_INTERFACE_TIME__

class I_Time
{
public:
	virtual float getDeltaTime() = 0;
	virtual float getFixedDeltaTime() = 0;
	virtual float getTime() = 0;
};


#endif // !__CAPS_INTERFACE_TIME__
