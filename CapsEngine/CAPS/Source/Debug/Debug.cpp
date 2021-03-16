#include "Debug.hpp"

namespace Ge
{
	I_Debug * Debug::p_debug = nullptr;	
	ConsoleDebug * Debug::p_consoleDebug = nullptr;
	
	bool Debug::Initialize(ptrF * ptrf)
	{
		Debug::p_debug = this;
		ptrf->Debug = this;		
		return true;
	}

	void Debug::Release()
	{
		Debug::p_debug = nullptr;
	}

	void Debug::Log(const char *format,...)
	{
		
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][USER] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][USER] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cout << buffer2;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(1.0f,1.0f,1.0f,1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::Error(const char *format,...)
	{
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][ERROR] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][ERROR] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cerr << termcolor::red << buffer2 << termcolor::reset;
		std::cin.ignore();
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.5f, 0.0f, 0.0f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::Warn(const char *format,...)
	{
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][WARN] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][WARN] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cout << termcolor::yellow << buffer2 << termcolor::reset;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.5f, 0.5f, 0.0f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::Info(const char *format,...)
	{		
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][INFO] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][INFO] : %s\n",buffer);
			#endif
		va_end (argList);
		
		std::cout << termcolor::cyan << buffer2 << termcolor::reset;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.0f, 0.4f, 0.4f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::VLayer(const char * format, ...)
	{
		char buffer[1000];
		char buffer2[1000];

				va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][VLAYER] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][VLAYER] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cout << termcolor::magenta << buffer2 << termcolor::reset;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.25f, 0.0f, 0.5f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::log(const char * format, ...)
	{
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][USER] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][USER] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cout << buffer2;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(1.0f,1.0f,1.0f,1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::error(const char * format, ...)
	{
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][ERROR] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][ERROR] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cerr << termcolor::red << buffer2 << termcolor::reset;
		std::cin.ignore();
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.5f, 0.0f, 0.0f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::warn(const char * format, ...)
	{
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][WARN] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][WARN] : %s\n",buffer);
			#endif
		va_end (argList);

		std::cout << termcolor::yellow << buffer2 << termcolor::reset;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.5f, 0.5f, 0.0f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::info(const char * format, ...)
	{
		char buffer[1000];
		char buffer2[1000];

		va_list argList;					
		va_start(argList,format);	
			#ifdef _WIN32
			vsprintf(buffer, format, argList);
			sprintf_s(buffer2, "[CAPS][INFO] : %s\n", buffer);	
			#elif __unix__
			vsprintf(buffer,format,argList);	
			sprintf(buffer2, "[CAPS][INFO] : %s\n",buffer);
			#endif
		va_end (argList);
		
		std::cout << termcolor::cyan << buffer2 << termcolor::reset;
		if (p_consoleDebug)
		{
			p_consoleDebug->setBaseColor(ImColor(0.0f, 0.4f, 0.4f, 1.0f));
			p_consoleDebug->AddLog("%s",buffer2);
		}
	}

	void Debug::setConsoleDebug(ConsoleDebug * cd)
	{
		p_consoleDebug = cd;
	}
}