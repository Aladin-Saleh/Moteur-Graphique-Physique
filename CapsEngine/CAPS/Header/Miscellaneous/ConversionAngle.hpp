#ifndef __CAPS_CONVERSION_ANGLE__
#define __CAPS_CONVERSION_ANGLE__

#include "Vector3.hpp"
#include "Vector4.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#define PI 3.14159265359f
const float radToDeg = 180.0f / PI;
const float degToRad = PI / 180.0f;

namespace Ge
{
	class ConversionAngle
	{
	public:
		static glm::mat4 mat4FromEulerDeg(Vector3 euler);
		static glm::mat4 quatToMat4(Vector4 rotation);
		static Vector4 FromEulerDeg(Vector3 euler);
		static Vector3 ToEulerDeg(Vector4 rotation);
		static float NormalizeAngle(float angle);
		static Vector3 NormalizeAngles(Vector3 angles);
	};
}

#endif //!__CAPS_CONVERSION_ANGLE__