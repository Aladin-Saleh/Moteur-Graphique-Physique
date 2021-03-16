#ifndef __CAPS_HIEARCHY__
#define __CAPS_HIEARCHY__

#include "imgui-cmake/Header/imgui.h"
#include "Model_Manager.hpp"
#include "LightManager.hpp"
#include "PhysicsEngine.hpp"
#include "SoundEngine.hpp"
#include "VulkanMisc.hpp"
#include "CameraManager.hpp"
#include <map>

namespace Ge
{
	class HiearchyGUI
	{
	public:
		HiearchyGUI(Model_Manager * mm, LightManager * lm, PhysicsEngine * pe, SoundEngine * se, CameraManager * cm);
		void OnGUI(VulkanMisc * vM);
	private:
		Model_Manager * m_ModelManager;
		LightManager * m_LightManager;
		PhysicsEngine * m_PhysicsEngine;
		SoundEngine * m_SoundEngine;
		CameraManager * m_cameraManager;
		ImGuiWindowFlags window_flags;
		int m_listboxCurrentItem = 0;
	};
}

#endif // !__CAPS_HIEARCHY__
