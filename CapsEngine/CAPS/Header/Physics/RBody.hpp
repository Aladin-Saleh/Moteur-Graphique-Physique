#ifndef __CAPS_RIGID_BODY__
#define __CAPS_RIGID_BODY__

#include "btBulletDynamicsCommon.h"
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
#include "RigidBody.hpp"
#include "CBoxShape.hpp"
#include <vector>
#include "Debug.hpp"
#include "ConversionAngle.hpp"
#include "GObject.hpp"

namespace Ge
{
	class RBody : public RigidBody, public virtual GObject
	{
	public:
		RBody(btDynamicsWorld* world, CShape * cshape, bool inertie);
		void Translate(Vector3 translate);
		void setPosition(Vector3 pos) override;
		void setRotation(Vector4 rot) override;
		void setEulerAngles(Vector3 eul) override;
		Vector3 getPosition() override;
		Vector4 getRotation() override;
		Vector3 getEulerAngles() override;
		void SetMass(float mass);
		void SetGravity(Vector3 gravity);
		void SetRestitution(float coef);
		void SetLinearVelocity(Vector3 velocity);
		Vector3 GetLinearVelocity();
		void ApplyImpulse(Vector3 impulse, Vector3 real_pos);
		void SetSleepingThreshold(float linear, float angular);
		void SetActiveCollision(bool activeCol);
		bool GetActiveCollision() const;
		void forceActivationState(int newState);
		void OnGUI() override;
		~RBody();
	private:
		friend class PhysicsEngine;
		inline btRigidBody * GetBody()
		{
			return m_pBody;
		}
		btDynamicsWorld * m_pWorld = nullptr;
		btRigidBody * m_pBody = nullptr;
		btDefaultMotionState * m_pMotionState = nullptr;
		CShape * m_pShape = nullptr;
		float m_gravity[3];
		float m_velocity[3];
		int style_idx = -1;
		bool m_activeCollision = false;
	};
}

#endif //!__CAPS_RIGID_BODY__