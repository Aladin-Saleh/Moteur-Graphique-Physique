#include "RayCast.hpp"
#include <string>

namespace Ge
{
	bool RayCast::Ray(Vector3 pos, Vector3 dir, Hit * hit, float maxDistance, std::string tag)
	{
		glm::vec3 position = glm::vec3(pos.x, pos.y, pos.z);
		glm::vec3 direction = glm::vec3(dir.x, dir.y, dir.z);
		std::vector<Vertex> vertexModels;
		glm::mat4 matriceObj;
		glm::mat4 rotateObj;
		std::vector<glm::vec3> m_matricePos;
		bool find = false;
		hit->distance = FLT_MAX;
		float t, u, v;

		if (!tag.compare("all"))
		{
			for (MShape* ms : *m_modelsListe)
			{
				vertexModels = ms->getModelBuffer()->GetVertices();
				matriceObj = ms->getUBO().model;
				m_matricePos.clear();
				for (int p = 0; p < vertexModels.size(); p++)
				{
					m_matricePos.push_back(matriceObj * glm::vec4(vertexModels[p].pos, 1.0f));
				}
				rotateObj = glm::rotate(matriceObj, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				for (int j = 0; j < vertexModels.size(); j++)
				{
					m_matricePos.push_back(rotateObj * glm::vec4(vertexModels[j].pos, 1.0f));
				}
				for (int i = 2; i+2 < m_matricePos.size();i += 3)
				{

					if (intersect_triangle(position, direction, m_matricePos[i], m_matricePos[i + 1], m_matricePos[i + 2], &t, &u, &v))
					{
						if (hit->distance > t && t > 0 && t < maxDistance)
						{
							hit->distance = t;
							hit->model = ms;
							glm::vec3 normalC = matriceObj * glm::vec4(vertexModels[i%vertexModels.size()].color, 0.0f);
							hit->normal = Vector3(normalC.x, normalC.y, normalC.z);
							hit->position = Vector3(direction.x*t, direction.y*t, direction.z*t) + pos;
							find = true;
						}
					}
				}
			}
		}
		else
		{
			for (MShape* ms : *m_modelsListe)
			{
				if (!tag.compare(ms->GetTag()))
				{
					vertexModels = ms->getModelBuffer()->GetVertices();
					matriceObj = ms->getUBO().model;
					m_matricePos.clear();
					for (int p = 0; p < vertexModels.size(); p++)
					{
						m_matricePos.push_back(matriceObj * glm::vec4(vertexModels[p].pos, 1.0f));
					}
					rotateObj = glm::rotate(matriceObj, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					for (int j = 0; j < vertexModels.size(); j++)
					{
						m_matricePos.push_back(rotateObj * glm::vec4(vertexModels[j].pos, 1.0f));
					}
					for (int i = 2; i+2 < m_matricePos.size(); i += 3)
					{
						if (intersect_triangle(position, direction, m_matricePos[i], m_matricePos[i+1], m_matricePos[i+2], &t, &u, &v))
						{
							if (hit->distance > t && t > 0 && t < maxDistance)
							{
								hit->distance = t;
								hit->model = ms;
								glm::vec3 normalC = matriceObj * glm::vec4(vertexModels[i%vertexModels.size()].color, 0.0f);
								hit->normal = Vector3(normalC.x, normalC.y, normalC.z);
								hit->position = Vector3(direction.x*t, direction.y*t, direction.z*t) + pos;
								find = true;
							}
						}
					}
				}
			}
		}
		return find;
	}

	void RayCast::Initialize(std::vector<MShape*>* modelsListe)
	{
		m_modelsListe = modelsListe;
	}

	bool RayCast::intersect_triangle(glm::vec3 orig, glm::vec3 dir, glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, float* t, float* u, float* v)
	{
		glm::vec3 edge1, edge2, tvec, pvec, qvec;
		float det, inv_det;

		/* find vectors for two edges sharing vert0*/
		edge1 = vert1- vert0;
		edge2 = vert2 - vert0;

		/* begin calculating determinant - also used to calculate U parameter */
		pvec = RayCast::cross(dir, edge2);

		/* if determinant is near zero, ray lies in plane of triangle */
		det = RayCast::dot(edge1, pvec);

#ifdef TEST_CULL /* define TEST_CULL if culling is desired */
		if (det < EPSILON) {
			return false;
		}

		/* calculate distance from vert0 to ray origin */
		tvec = orig - vert0;

		/* calculate U parameter and test bounds */
		*u = RayCast::dot(tvec, pvec);
		if (*u < 0.0 || *u > det) {
			return false;
		}

		/* prepare to test V parameter */
		qvec = RayCast::cross(tvec, edge1);

		/* calculate V parameter and test bounds */
		*v = RayCast::dot(dir, qvec);
		if (*v < 0.0 || *u + *v > det) {
			return false;
		}

		/* calculate t, scale parameters, ray intersects triangle */
		*t = RayCast::dot(edge2, qvec);
		inv_det = 1.0f / det;
		*t *= inv_det;
		*u *= inv_det;
		*v *= inv_det;
#else /* the non-culling branch */
		if (det > -EPSILON && det < EPSILON) {
			return false;
		}
		inv_det = 1.0f / det;

		/* calculate distance from vert0 to ray origin */

		tvec = orig - vert0;

		/* prepare to test V parameter */

		qvec = RayCast::cross(tvec, edge1);

		/* calculate V parameter and test bounds */
		*v = RayCast::dot(dir, qvec) * inv_det;
		if (*v < 0.0f || *u + *v > 1.0f) {
			return false;
		}

		/* calculate t, ray intersects triangle */
		*t = RayCast::dot(edge2, qvec) * inv_det;

#endif // TEST_CULL
		return true;
	}

	glm::vec3 RayCast::cross(glm::vec3 v1, glm::vec3 v2)
	{
		return glm::vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	float RayCast::dot(glm::vec3 v1, glm::vec3 v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

}
