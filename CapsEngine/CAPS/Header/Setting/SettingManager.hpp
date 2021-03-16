#ifndef __CAPS_SETTING_MANAGER__
#define __CAPS_SETTING_MANAGER__

#include "glm/glm.hpp"
#include "Debug.hpp"
#include "SettingManagerStruct.hpp"
#include "I_SettingManager.hpp"
#include "PointeurFonction.hpp"

namespace Ge
{
	class SettingManager : public I_SettingManager
	{
		struct SettingInfo
		{
			double m_fps = 60;
			double m_sizeHeightWindow = 800;
			double m_sizeWidthWindow = 1200;
			const char * m_name = "ProjectName";
			float m_gamma = 1.0f;
			Vector3 m_gravity = Vector3(0, -9.81f, 0);
			version m_version;
			Vector4 m_clearColor = Vector4(1.0f);			
		};
	public:
		double GetFps();
		void SetFps(double fps);
		const char* GetName();
		void SetName(const char* name);
		double GetWindowHeight();
		void SetWindowHeight(double height);
		double GetWindowWidth();
		void SetWindowWidth(double Width);
		Vector3 GetGravity();
		void SetGravity(Vector3 gravity);
		void SetVersion(version v);
		version GetVersion();
		void SetClearColor(Vector4 color);
		Vector4 GetClearColor();
		void SetGamma(float gamma);
		float GetGamma();
	private:
		friend class GameEngine;
		bool Initialize(ptrF * ptrf);
		void Release();
	private:
		SettingInfo m_settingInfo;
	};
}
#endif