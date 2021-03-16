#include "CVertexShape.hpp"
#include "Model_Manager.hpp"

namespace Ge
{
	CVertexShape::CVertexShape(float mass, ShapeBuffer * sb) : CShape(mass)
	{
		m_triangleMesh = new btTriangleMesh();
		ModelBuffer * mb = Model_Manager::CastModelBuffer(sb);
		if (mb)
		{
			isInertieAvailable = false;
			std::vector<Vertex> vertex = mb->GetVertices();
			size_t size = vertex.size();

			for (size_t i = 0ul; i < size; i += 3)
			{
				m_triangleMesh->addTriangle(
					btVector3(vertex[i].pos.x, vertex[i].pos.y, vertex[i].pos.z),
					btVector3(vertex[i + 1].pos.x, vertex[i + 1].pos.y, vertex[i + 1].pos.z),
					btVector3(vertex[i + 2].pos.x, vertex[i + 2].pos.y, vertex[i + 2].pos.z)
				);
			}

			m_pShape = new btBvhTriangleMeshShape(m_triangleMesh, true, true);
		}
	}


	CVertexShape::~CVertexShape()
	{
		delete m_triangleMesh;
	}
}
