#include "LSpot.hpp"

namespace Ge
{
	LSpot::LSpot(int index, VulkanMisc * vM) : Lights(index, vM)
	{
		m_ubl.constant = 1.0f;
		m_ubl.linear = 0.09f;
		m_ubl.quadratic = 0.032f;
		m_ubl.cutOff = 1.0f;
		m_ubl.outerCutOff = 2.0f;
		m_ubl.status = 2;
	}

	float LSpot::GetConstant()
	{
		return m_ubl.constant;
	}

	void LSpot::SetConstant(float constant)
	{
		m_ubl.constant = constant;
	}

	float LSpot::GetLinear()
	{
		return m_ubl.linear;
	}

	void LSpot::SetLinear(float linear)
	{
		m_ubl.linear = linear;
	}

	float LSpot::GetQuadratic()
	{
		return m_ubl.quadratic;
	}

	void LSpot::SetQuadratic(float quadratic)
	{
		m_ubl.quadratic = quadratic;
	}

	float LSpot::GetCutOff()
	{
		return m_ubl.cutOff;
	}

	void LSpot::SetCutOff(float cutOff)
	{
		m_ubl.cutOff = cutOff;
	}

	float LSpot::GetOuterCutOff()
	{
		return m_ubl.outerCutOff;
	}

	void LSpot::SetOuterCutOff(float outerCutOff)
	{
		m_ubl.outerCutOff = outerCutOff;
	}
}