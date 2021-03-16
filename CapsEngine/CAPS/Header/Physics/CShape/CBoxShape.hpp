#ifndef __CAPS_BOX_SHAPE__
#define __CAPS_BOX_SHAPE__

#include "CShape.hpp"
#include "CollisionBoxShape.hpp"

namespace Ge
{
	class CBoxShape : public CShape, public CollisionBoxShape
	{
	public:
		CBoxShape(Vector3 halfExtents, float mass);
	protected:
		Vector3 m_halfExtents;
	};
}

#endif //!__CAPS_BOX_SHAPE__