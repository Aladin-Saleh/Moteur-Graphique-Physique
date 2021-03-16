#ifndef __CAPS_DEBUG__
#define __CAPS_DEBUG__

#include "termcolor/termcolor.hpp"
#include <iostream>
#include <cstdarg>
#include "I_Debug.hpp"
#include "PointeurFonction.hpp"
#include "Caps_Console_HUD.hpp"

#ifdef NDEBUG
#if defined(_WIN32) || defined(_WIN64)
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#elif defined(__APPLE__)

#elif defined(__unix__) || defined(__unix)

#else
#error plate-forme non prise en charge
#endif
#endif

namespace Ge
{
	class Debug : public I_Debug
	{
	public:
		bool Initialize(ptrF * ptrf);
		void Release();
		static void Log(const char *format, ...);
		static void Error(const char *format, ...);
		static void Warn(const char *format, ...);
		static void Info(const char *format, ...);
		static void VLayer(const char *format, ...);
		void log(const char *format, ...);
		void error(const char *format, ...);
		void warn(const char *format, ...);
		void info(const char *format, ...);
		void setConsoleDebug(ConsoleDebug * cd);
	private:		
		static I_Debug * p_debug;		
		static ConsoleDebug * p_consoleDebug;
	};
}

#endif	// __CAPS_DEBUG__