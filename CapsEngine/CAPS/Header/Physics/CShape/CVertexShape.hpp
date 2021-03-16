#ifndef __CAPS_COLLISION_VERTEX_SHAPE__
#define __CAPS_COLLISION_VERTEX_SHAPE__

#include "CollisionVertexShape.hpp"
#include "CShape.hpp"

namespace Ge
{
	class CVertexShape : public CShape, public CollisionVertexShape
	{
	public:
		CVertexShape(float mass, ShapeBuffer * sb);
		~CVertexShape() override;
	protected:
		btTriangleMesh * m_triangleMesh;
	};
}

#endif //!__CAPS_COLLISION_VERTEX_SHAPE__