#include "FlyCamera.hpp"
#include "Time.hpp"

namespace Ge
{
	FlyCamera::FlyCamera(I_InputManager * input, Camera * cam)
	{
		iM = input;
		camera = cam;
		m_angleY = 0.0f;
		m_angleX = 0.0f;
		m_moveSpeed = 0.0f;
	}

	void FlyCamera::UpdateCamera()
	{
		if (iM->GetKey(340))
		{
			m_addMoveSpeed += Time::GetDeltaTime() * m_fastSpeedMult;
		}
		else
		{
			m_addMoveSpeed = 0.0f;
		}
		m_moveSpeed = Time::GetDeltaTime() * m_maxSpeed;
		m_moveSpeed += m_addMoveSpeed;

		if (iM->GetMouse(1))
		{
			m_angleY += iM->AxisMouseY() * m_maxSpeedRotate;
			m_angleX += iM->AxisMouseX() * m_maxSpeedRotate;
		}

		if (iM->GetKey(87))
		{
			camera->setPosition(camera->getPosition() - camera->transformDirectionAxeX() * m_moveSpeed);
		}
		else if (iM->GetKey(83))
		{
			camera->setPosition(camera->getPosition() - camera->transformDirectionAxeX() * -m_moveSpeed);
		}

		if (iM->GetKey(68))
		{
			camera->setPosition(camera->getPosition() - camera->transformDirectionAxeY() * m_moveSpeed);
		}
		else if (iM->GetKey(65))
		{
			camera->setPosition(camera->getPosition() - camera->transformDirectionAxeY() * -m_moveSpeed);
		}

		if (iM->GetKey(341))
		{
			camera->setPosition(camera->getPosition() - Vector3(0, 1, 0) * m_moveSpeed);
		}
		else if (iM->GetKey(32))
		{
			camera->setPosition(camera->getPosition() - Vector3(0, -1, 0) * m_moveSpeed);
		}
		camera->setEulerAngles(Vector3(m_angleY, m_angleX, 0.0f));
	}
}