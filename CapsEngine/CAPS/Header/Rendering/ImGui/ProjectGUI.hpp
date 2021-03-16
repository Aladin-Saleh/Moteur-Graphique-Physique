#ifndef __CAPS_PROJECT_GUI__
#define __CAPS_PROJECT_GUI__

#include "imgui-cmake/Header/imgui.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include <filesystem> // windows
#include "VulkanMisc.hpp"
#include "BrancheUI.hpp"
#include "Debug.hpp"

namespace Ge
{
	class ProjectGUI
	{
	public:
		ProjectGUI();
		void OnGUI(VulkanMisc * vM);
		~ProjectGUI();
	private:
		void RecurseImGui(BrancheUI * b, int indentLevels);
		void RecreateTree();
	private:
		BrancheUI * m_brancheUI;
		ImGuiWindowFlags window_flags;
		std::string path;
	};
}

#endif //!__CAPS_PROJECT_GUI__