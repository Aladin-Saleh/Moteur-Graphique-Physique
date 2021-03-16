#ifndef __CAPS_MODEL_MANAGER__
#define __CAPS_MODEL_MANAGER__

#include "Debug.hpp"
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "MShape.hpp"
#include "I_ModelManager.hpp"
#include "VulkanMisc.hpp"
#include <map>
#include "RayCast.hpp"

using namespace Ge;
namespace std //pour combiner correctement les champs d'une structure
{
	template<> struct hash<Vertex>
	{
		size_t operator()(Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}
namespace Ge
{
	class Model_Manager : public I_ModelManager
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release(VkDevice device);
	public:
		ShapeBuffer * AllocateBuffer(const char * path);
		Model * CreateModel(ShapeBuffer * buffer, std::string nom ="Model");
		void DestroyModel(Model * model);
		void DestroyBuffer(ShapeBuffer * buffer);

		void Render(VkCommandBuffer CmdBuffer, VkDescriptorSet pDescriptorSets, VkPipelineLayout pipelineLayout);
		void UpdateUniformBufferObject(Camera * cam);
		uint32_t ModelCount();
		std::vector<MShape *> getModels();
		VkBuffer getUniformBuffers();
		bool recreateDescripteurModels();
		bool destoyModelStateBuffer();
		void DestroyModelBuffer();
		void MajTexture();
		RayCast * getRayCast();
		static ModelBuffer * CastModelBuffer(ShapeBuffer * sb);
	private:
		std::map<Model *, MShape *> m_MapModels;
		static std::map<ShapeBuffer *, ModelBuffer *> m_MapModelsBuffers;
		std::vector<MShape *> m_models;
		std::vector<ModelBuffer *> m_modelBuffers;
		VulkanMisc * m_vM;
		VmaBuffer m_vmaUniformBuffers;
		RayCast m_RayCast;
		bool m_recreateDescripteur = false;
		bool m_destroy = false;
	};
}

#endif