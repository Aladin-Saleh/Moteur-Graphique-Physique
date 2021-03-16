#ifndef __CAPS_CAMERA_MANAGER__
#define __CAPS_CAMERA_MANAGER__

#include <vector>
#include "Camera.hpp"
#include "Debug.hpp"
#include "I_CameraManager.hpp"
#include "VulkanMisc.hpp"
#include "FlyCamera.hpp"

namespace Ge
{
	class CameraManager : public I_CameraManager
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanSwapChainMisc * vM, I_InputManager * input);
		void Release();
	public:
		I_Camera * AllocateCamera(std::string name = "Camera");
		void ReleaseCamera(I_Camera * camera);
		void updateAspectRatio();
		void UpdateFlyCamera();
		static void updateSelectCamera();
		I_Camera * getCurrentCamera();
		Camera * getbaseCam();
		std::vector<Camera *> getCameras();
		void SetFlyCamera(bool state);
	private:
		static CameraManager * s_pIstance;
		VulkanSwapChainMisc * m_vulkanSwapChainMisc;
		std::vector<Camera *> m_cameras;
		FlyCamera * flc;
		Camera * m_baseCam;
		int m_selectCamera = -1;
		bool m_flyCamera = true;
	};
}

#endif //!__CAPS_CAMERA_MANAGER__