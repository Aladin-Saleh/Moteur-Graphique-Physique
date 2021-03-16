#ifndef __CAPS_GRAPHIC_OBJECT__
#define __CAPS_GRAPHIC_OBJECT__

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp" 
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/common.hpp"
#include "GraphicsObject.hpp"
#include "Debug.hpp"
#include "Component.hpp"
#include "imgui-cmake/Header/imgui.h"
#include <vector>
#include <string> 

namespace Ge
{
	class GObject : virtual public GraphicsObject
	{
		struct Transform
		{
			glm::mat4 rotationMatrix;
			glm::mat4 translateMatrix;
			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 target;
			glm::quat rotation;
			glm::vec3 eulerAngles;
			glm::vec3 scale;
			Vector3  pos;
			Vector4  rot;
			Vector3  eul;
			Vector3  dir;
			Vector3  size;
		};
		struct TransformImgui
		{
			float pos[3];
			float rot[4];
			float eul[3];
			float dir[3];
			float size[3];
		};
	public:
		GObject(bool inverse = false);
		void setName(std::string nom);
		std::string * getName();
		virtual void setPosition(Vector3 pos);
		virtual void setRotation(Vector4 rot);
		virtual void setEulerAngles(Vector3 eul);
		virtual void setScale(Vector3 scale);
		virtual void setTarget(Vector3 target);
		virtual Vector3 getPosition();
		virtual Vector4 getRotation();
		virtual Vector3 getEulerAngles();
		virtual Vector3 getScale();
		Vector3 transformDirectionAxeX();
		Vector3 transformDirectionAxeY();
		Vector3 transformDirectionAxeZ();
		Vector3 transformDirectionAxe(Vector3 dir);
		bool getFlipY();
		void setFlipY(bool state);
		void addComponent(Component * c);
		void removeComponent(Component * c);
		virtual void OnGUI();
	protected:
		std::string m_nom;
		std::string m_nomTemp;
		bool m_changeGetRE = false;
		bool m_changetarget = false;
		bool m_flipY = false;
		bool m_inversePos = true;
		Transform m_transform{};
		TransformImgui m_transformImgui{};
		std::vector<Component *> m_Component;
	};
}

#endif // !__CAPS_GRAPHIC_OBJECT__