#include "ConversionAngle.hpp"

namespace Ge
{
	glm::mat4 ConversionAngle::mat4FromEulerDeg(Vector3 euler)
	{
		glm::mat4 RotationMatrix;
		RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(euler.y), glm::vec3(0.0f, 1.0f, 0.0f));
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(euler.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return RotationMatrix;
	}

	glm::mat4 ConversionAngle::quatToMat4(Vector4 rotation)
	{
		glm::quat q(rotation.w, rotation.x, rotation.y, rotation.z);
		return toMat4(q);
	}

	Vector4 ConversionAngle::FromEulerDeg(Vector3 euler)
	{
		glm::mat4 RotationMatrix;
		RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(euler.y), glm::vec3(0.0f, 1.0f, 0.0f));
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(euler.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::quat quaternion = toQuat(RotationMatrix);
		return Vector4(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
	}

	Vector3 ConversionAngle::ToEulerDeg(Vector4 rotation)
	{
		glm::quat q(rotation.w, rotation.x, rotation.y, rotation.z);
		glm::vec3 euler;
		glm::mat4 rotationMatrix = toMat4(q);
		glm::extractEulerAngleXYZ(rotationMatrix, euler.x, euler.y, euler.z);
		euler = glm::degrees(euler);
		return Vector3(euler.x, euler.y, euler.z);
	}

	float ConversionAngle::NormalizeAngle(float angle)
	{
		while (angle > 360)
			angle -= 360;
		while (angle < 0)
			angle += 360;
		return angle;
	}

	Vector3 ConversionAngle::NormalizeAngles(Vector3 angles)
	{
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		angles.z = NormalizeAngle(angles.z);
		return angles;
	}
}
