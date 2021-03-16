#ifndef __CAPS_INTERFACE_DEBUG__
#define __CAPS_INTERFACE_DEBUG__

class I_Debug
{
public:
	virtual void log(const char *format, ...) = 0;
	virtual void error(const char *format, ...) = 0;
	virtual void warn(const char *format, ...) = 0;
	virtual void info(const char *format, ...) = 0;
};

#endif	// !__CAPS_INTERFACE_DEBUG__