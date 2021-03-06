#ifndef __CAPS_TIME__
#define __CAPS_TIME__

#include "Debug.hpp"
#include "I_Time.hpp"
#include <chrono>

namespace Ge
{
	class Time : public I_Time
	{
	private:
		friend class GameEngine;
		void StartTime();
		void FixedUpdateTime();
		void UpdateTime();
		void Release();
	public:
		float getDeltaTime();
		float getFixedDeltaTime();
		float getTime();
		static float GetFixedDeltaTime();
		static float GetDeltaTime();
		static float GetTime();
	private:
		static Time * s_pInstance;
#ifdef _WIN32
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_currentTimeF;
		std::chrono::steady_clock::time_point m_lastTimeF;
		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_lastTime;
#elif __unix__
		std::chrono::_V2::system_clock::time_point m_startTime;
		std::chrono::_V2::system_clock::time_point m_currentTimeF;
		std::chrono::_V2::system_clock::time_point m_lastTimeF;
		std::chrono::_V2::system_clock::time_point m_currentTime;
		std::chrono::_V2::system_clock::time_point m_lastTime;
#endif
		float m_time = 0.0f;
		float m_deltaTime = 0.0f;		
		float m_fixedDeltaTime = 0.0f;
	};
}

#endif // !__CAPS_TIME__
