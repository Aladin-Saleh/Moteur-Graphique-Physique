#include "CameraManager.hpp"

namespace Ge
{
	CameraManager * CameraManager::s_pIstance = nullptr;
	bool CameraManager::Initialize(VulkanSwapChainMisc * vM, I_InputManager * input)
	{
		m_baseCam = new Camera(vM);
		m_baseCam->setName("Default Camera");
		m_selectCamera = -1;
		m_vulkanSwapChainMisc = vM;
		flc = new FlyCamera(input,m_baseCam);
		m_cameras.push_back(m_baseCam);
		CameraManager::s_pIstance = this;
		return true;
	}

	void CameraManager::Release()
	{
		for (Camera * cameras : m_cameras)
		{
			delete(cameras);
		}
		delete(flc);
		CameraManager::s_pIstance = nullptr;
	}

	I_Camera * CameraManager::AllocateCamera(std::string name)
	{
		Camera * cam = new Camera(m_vulkanSwapChainMisc);
		m_cameras.push_back(cam);
		cam->setName(name);
		CameraManager::updateSelectCamera();
		return cam;
	}

	void CameraManager::ReleaseCamera(I_Camera * camera)
	{
		for (Camera * cameras : m_cameras)
		{
			if (cameras == camera)
			{
				delete(cameras);
				break;
			}
		}
		CameraManager::updateSelectCamera();
	}

	void CameraManager::updateAspectRatio()
	{
		for (Camera * cameras : m_cameras)
		{
			cameras->updatePerspective();
		}
		m_baseCam->updatePerspective();
	}

	void CameraManager::UpdateFlyCamera()
	{
		if (m_flyCamera && m_selectCamera < 0)
		{
			flc->UpdateCamera();
		}
	}

	void CameraManager::updateSelectCamera()
	{
		int minimum = INT_MAX;

		for (unsigned i = 0; i < s_pIstance->m_cameras.size() ;i++)
		{
			if (s_pIstance->m_cameras[i]->getPriority() < minimum)
			{
				minimum = s_pIstance->m_cameras[i]->getPriority();
				s_pIstance->m_selectCamera = i;
			}
		} 
	}

	I_Camera * CameraManager::getCurrentCamera()
	{
		if (m_selectCamera < 0)
		{
			return m_baseCam;
		}
		else
		{
			return m_cameras[m_selectCamera];
		}	
	}

	Camera * CameraManager::getbaseCam()
	{
		return m_baseCam;
	}

	std::vector<Camera*> CameraManager::getCameras()
	{
		return m_cameras;
	}

	void CameraManager::SetFlyCamera(bool state)
	{
		m_flyCamera = state;
	}
}