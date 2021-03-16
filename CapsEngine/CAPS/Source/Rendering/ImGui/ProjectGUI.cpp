#include "ProjectGUI.hpp"
#include <functional>

//namespace fs = std::filesystem;

namespace Ge
{
	ProjectGUI::ProjectGUI()
	{
		/*path = "../CAPSDLL";
		fs::path p = path;
		m_brancheUI = new BrancheUI(p);
		window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoNav;*/
	}

	void ProjectGUI::OnGUI(VulkanMisc * vM)
	{
		/*ImGui::Begin("Projet", nullptr, window_flags);
		ImGui::SetWindowPos("Projet", ImVec2(vM->str_VulkanSwapChainMisc->str_swapChainExtent.width - vM->str_VulkanSwapChainMisc->str_swapChainExtent.width / 5.0f, 170.0f));
		ImGui::SetWindowSize("Projet", ImVec2(vM->str_VulkanSwapChainMisc->str_swapChainExtent.width / 5.0f, vM->str_VulkanSwapChainMisc->str_swapChainExtent.height-170.0f));
		RecurseImGui(m_brancheUI, 0);
		ImGui::End();*/
	}

	ProjectGUI::~ProjectGUI()
	{
		//delete(m_brancheUI);
	}

	void ProjectGUI::RecurseImGui(BrancheUI * b, int indentLevels)
	{
		/*//static bool test[10];
		for (int i = 0; i < indentLevels; ++i)
		{
			ImGui::Indent();
		}
		for (FeuilleUI * f : m_brancheUI->getF())
		{
			//ImGui::Text(f->getPath().filename().string().c_str());
		}
		for (int i = 0; i < m_brancheUI->getB().size(); i++)
		{
			if (ImGui::MenuItem(m_brancheUI->getB()[i]->getPath().filename().string().c_str()))
			{
				RecurseImGui(m_brancheUI->getB()[i], indentLevels+1);
				
			}
		}
		for (int i = 0; i < indentLevels; ++i)
		{
			ImGui::Unindent();
		}*/
	}

	void ProjectGUI::RecreateTree()
	{
		/*delete(m_brancheUI);
		fs::path p = path;
		m_brancheUI = new BrancheUI(p);*/
	}
}