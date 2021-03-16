#include "HiearchyGUI.hpp"

namespace Ge
{
	HiearchyGUI::HiearchyGUI(Model_Manager * mm, LightManager * lm, PhysicsEngine * pe, SoundEngine * se, CameraManager * cm)
	{
		m_ModelManager = mm;
		m_LightManager = lm;
		m_PhysicsEngine = pe;
		m_SoundEngine = se;
		m_cameraManager = cm;
		window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoInputs;
		window_flags |= ImGuiWindowFlags_NoFocusOnAppearing;
		window_flags |= ImGuiWindowFlags_NoNav;
	}

	void HiearchyGUI::OnGUI(VulkanMisc * vM)
	{
		std::vector<GObject *>  items;
		std::vector<const char *> cnames;
		std::vector<MShape *> models = m_ModelManager->getModels();
		std::vector<Lights *> lights = m_LightManager->GetLights();
		std::vector<AudioSource *> sources = m_SoundEngine->getAudioSources();
		std::vector<RBody *> rigidBodys = m_PhysicsEngine->getRigidBody();
		std::vector<Camera *> cams = m_cameraManager->getCameras();
		std::map<std::string, int> m_mapNB;

		for (Camera * ca : cams)
		{
			items.push_back(ca);
		}
		for (MShape * ms : models)
		{
			items.push_back(ms);
		}
		for (Lights * ls : lights)
		{
			items.push_back(ls);
		}
		for (AudioSource * as : sources)
		{
			items.push_back(as);
		}
		for (AudioSource * as : sources)
		{
			items.push_back(as);
		}
		for (RBody * rb : rigidBodys)
		{
			items.push_back(rb);
		}
		for (GObject * go : items)
		{
			m_mapNB[(*go->getName())]++;
			std::string * result = go->getName();
			if (m_mapNB[(*go->getName())] > 1)
			{
				*result += std::to_string(m_mapNB[(*go->getName())] - 1);
			}			
			cnames.push_back(result->c_str());		
		}

		ImGui::SetNextWindowBgAlpha(0.55f);
		if (ImGui::Begin("Scene explorer",nullptr , window_flags))
		{
			ImGui::SetWindowPos("Scene explorer", ImVec2(0,20));
			ImGui::SetWindowSize("Scene explorer", ImVec2(vM->str_VulkanSwapChainMisc->str_swapChainExtent.width/4.2f, vM->str_VulkanSwapChainMisc->str_swapChainExtent.height / 1.4f));
			ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Hierarchy\n\n");

			ImGui::PushItemWidth(280);
			ImGui::ListBox("###Hierarchy", &m_listboxCurrentItem, cnames.data(), cnames.size(), 12);
			ImGui::PopItemWidth();

			ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Inspector\n\n");
			if (items.size() > 0)
			{
				ImGui::BeginChild("");
				items[m_listboxCurrentItem]->OnGUI();
				ImGui::EndChild();
			}
		}
		ImGui::End();
	}
}