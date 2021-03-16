#include "CShape.hpp"

namespace Ge
{
	CShape::CShape(float mass)
	{
		m_mass = mass;
	}

	void CShape::SetMass(float mass)
	{
		m_mass = mass;
	}

	Vector3 CShape::GetInertia() const
	{
		btVector3 inertia;
		m_pShape->calculateLocalInertia(m_mass, inertia);
		return Vector3(inertia.x(), inertia.y(), inertia.z());
	}

	float CShape::GetMass() const
	{
		return m_mass;
	}

	btCollisionShape * CShape::GetShape()
	{
		return m_pShape;
	}

	CollisionShape * CShape::GetCollisionShape()
	{
		return this;
	}

	bool CShape::getIsInertieAvailable() 
	{
		return isInertieAvailable;
	}

	CShape::~CShape()
	{
		delete(m_pShape);
	}
}