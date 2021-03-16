#include "LPoint.hpp"

namespace Ge
{
	LPoint::LPoint(int index, VulkanMisc * vM) : Lights(index,vM)
	{
		m_ubl.constant = 1.0f;
		m_ubl.linear = 0.09f;
		m_ubl.quadratic = 0.032f;
		m_ubl.status = 1;
	}

	float LPoint::GetConstant()
	{
		return m_ubl.constant;
	}

	void LPoint::SetConstant(float constant)
	{
		m_ubl.constant = constant;
	}

	float LPoint::GetLinear()
	{
		return m_ubl.linear;
	}

	void LPoint::SetLinear(float linear)
	{
		m_ubl.linear = linear;
	}

	float LPoint::GetQuadratic()
	{
		return m_ubl.quadratic;
	}

	void LPoint::SetQuadratic(float quadratic)
	{
		m_ubl.quadratic = quadratic;
	}
}