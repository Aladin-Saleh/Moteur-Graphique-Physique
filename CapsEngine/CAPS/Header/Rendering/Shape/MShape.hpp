#ifndef __CAPS_MODEL_SHAPE__
#define __CAPS_MODEL_SHAPE__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "Camera.hpp"
#include "ModelBuffer.hpp"
#include "BufferManager.hpp"
#include "Model.hpp"
#include "Materials.hpp"
#include "GObject.hpp"

namespace Ge
{
	struct UniformBufferObject
	{
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};
	struct PushConstants
	{
		alignas(int) int ubo;
		alignas(int) int material;
	};
	class MShape : public Model, public virtual GObject
	{
	public:
		MShape(ModelBuffer * buffer, int indexUbo, VulkanMisc * vM);
		~MShape();
		void Render(VkCommandBuffer CmdBuffer, VkDescriptorSet pDescriptorSets, VkPipelineLayout pipelineLayout, VkShaderStageFlags pushConstantShaderFlags);
		void UpdateUniformBufferObject(Camera * cam);
		void SetMaterial(Material * material);
		Material * GetMaterial();
		VkBuffer GetUniformBuffers();
		ModelBuffer * getModelBuffer();
		void SetTag(std::string tag = "UnTagged");
		std::string GetTag();
		void Destroy();
		bool getDestroy();
		UniformBufferObject getUBO();
		void setIndexUbo(int index);
		void MajTexture();
	private:
		VulkanMisc * vMisc;
		ModelBuffer * m_buffer;
		VkDevice m_device;
		VmaBuffer m_vmaUniformBuffer;
		PushConstants m_index{};
		UniformBufferObject m_ubo{};
		Material * m_material;
		int m_indexUbo = 0;
		bool m_destroy = false;
		std::string m_tag = "UnTagged";
	};
}

#endif // !__CAPS_MODEL_SHAPE__
