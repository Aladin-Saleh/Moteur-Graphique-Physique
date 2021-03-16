#ifndef __CAPS_COLLISION_SHAPE__
#define __CAPS_COLLISION_SHAPE__

#include "btBulletDynamicsCommon.h"
#include "CollisionShape.hpp"
#include "Vector3.hpp"
#include "Debug.hpp"

namespace Ge
{
	class CShape : virtual public CollisionShape
	{
	public:
		CShape(float mass);
		void SetMass(float mass);
		Vector3 GetInertia() const;
		float GetMass() const;
		btCollisionShape * GetShape();
		CollisionShape * GetCollisionShape();
		bool getIsInertieAvailable();
		virtual ~CShape();
	protected:
		btCollisionShape * m_pShape = nullptr;
		btScalar m_inertia;
		float m_mass = 0;
		bool isInertieAvailable = true;
	};
}

#endif // !__CAPS_COLLISION_SHAPE__