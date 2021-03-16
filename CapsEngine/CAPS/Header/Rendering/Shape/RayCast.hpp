#ifndef __CAPS_RAY_CAST__
#define __CAPS_RAY_CAST__

#include "MShape.hpp"
#include "I_RayCast.hpp"

#define EPSILON 0.000001
#define TEST_CULL

namespace Ge
{
	class RayCast : public I_RayCast
	{
	public:
		bool Ray(Vector3 pos, Vector3 dir,Hit * hit, float maxDistance, std::string tag = "all");
	private:
		friend class Model_Manager;
		void Initialize(std::vector<MShape *> * modelsListe);
	private:
		bool intersect_triangle(glm::vec3 orig, glm::vec3 dir, glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, float* t, float* u, float* v);
		glm::vec3 cross(glm::vec3 v1, glm::vec3 v2);
		float dot(glm::vec3 v1, glm::vec3 v2);
	private:
		std::vector<MShape *> * m_modelsListe;
	};
}

#endif //!__CAPS_RAY_CAST__