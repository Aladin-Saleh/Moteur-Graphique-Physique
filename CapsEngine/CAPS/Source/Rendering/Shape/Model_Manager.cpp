#include "Model_Manager.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#include <glm/gtx/normal.hpp>

namespace Ge
{
	std::map<ShapeBuffer *, ModelBuffer *> Model_Manager::m_MapModelsBuffers;

	bool Model_Manager::Initialize(VulkanMisc * vM)
	{
		m_vM = vM;

		if (!BufferManager::createBuffer(8, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffers, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer");
			return false;
		}
		m_RayCast.Initialize(&m_models);
		Debug::Info("Initialisation du ModelManager");
		return true;
	}

	void Model_Manager::Release(VkDevice device)
	{
		for (MShape * ms : m_models)
		{
			delete(ms);
		}
		m_models.clear();
		m_MapModels.clear();
		for (ModelBuffer * buffer : m_modelBuffers)
		{
			delete(buffer);
		}
		m_modelBuffers.clear();
		m_MapModelsBuffers.clear();
		BufferManager::destroyBuffer(m_vmaUniformBuffers);
		Debug::Info("Liberation du ModelManager");
	}

	ShapeBuffer * Model_Manager::AllocateBuffer(const char * path)
	{
		//m_vM->str_VulkanInfo->model_info_name.push_back(path);
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		glm::vec3 normalResult;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path))
		{
			Debug::Warn("%s  %s", nullptr, warn.c_str(), err.c_str());
			return nullptr;
		}

		std::unordered_map<Vertex, uint32_t> uniqueVertices{};

		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{
				Vertex vertex{};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.color = {
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};

				if (uniqueVertices.count(vertex) == 0)
				{
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}

		ModelBuffer * buffer = new ModelBuffer(vertices, indices, m_vM);
		m_modelBuffers.push_back(buffer);
		m_MapModelsBuffers[(ShapeBuffer *)buffer] = buffer;
		return buffer;
	}

	Model * Model_Manager::CreateModel(ShapeBuffer * buffer, std::string nom)
	{
		ModelBuffer * mb = m_MapModelsBuffers[buffer];
		if (!mb)
		{
			Debug::Warn("Le buffer n'existe pas");
			return nullptr;
		}
		MShape * Mesh = new MShape(mb, m_models.size(), m_vM);
		Mesh->setName(nom);
		m_models.push_back(Mesh);
		m_MapModels[(Model *)Mesh] = Mesh;
		m_vM->str_VulkanDescriptor->modelCount = m_models.size();
		m_recreateDescripteur = true;
		return Mesh;
	}

	void Model_Manager::DestroyModel(Model * model)
	{
		MShape * ms = m_MapModels[model];
		if (ms)
		{
			ms->Destroy();

			m_recreateDescripteur = true;
			m_destroy = true;
		}
	}

	void Model_Manager::DestroyBuffer(ShapeBuffer * buffer)
	{
		for (MShape * ms : m_models)
		{
			if ((ShapeBuffer *)ms->getModelBuffer() == buffer)
			{
				ms->Destroy();
			}
		}
		for (ModelBuffer * mb : m_modelBuffers)
		{
			if ((ShapeBuffer *)mb == buffer)
			{
				mb->Destroy();
			}
		}
		m_recreateDescripteur = true;
		m_destroy = true;
	}

	void Model_Manager::Render(VkCommandBuffer CmdBuffer, VkDescriptorSet pDescriptorSets, VkPipelineLayout pipelineLayout)
	{
		for (MShape * mesh : m_models)
		{
			mesh->Render(CmdBuffer, pDescriptorSets, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);
		}
	}

	void Model_Manager::UpdateUniformBufferObject(Camera * cam)
	{
		for (MShape * mesh : m_models)
		{
			mesh->UpdateUniformBufferObject(cam);
		}
	}

	uint32_t Model_Manager::ModelCount()
	{
		return m_models.size();
	}

	std::vector<MShape*> Model_Manager::getModels()
	{
		return m_models;
	}

	VkBuffer Model_Manager::getUniformBuffers()
	{
		return m_vmaUniformBuffers.buffer;
	}

	bool Model_Manager::recreateDescripteurModels()
	{
		bool buf = m_recreateDescripteur;
		m_recreateDescripteur = false;
		return buf;
	}

	bool Model_Manager::destoyModelStateBuffer()
	{
		bool buf = m_destroy;
		m_destroy = false;
		return buf;
	}

	void Model_Manager::DestroyModelBuffer()
	{
		MShape * ms;
		ModelBuffer * mb;
		for (int i = 0; i < m_models.size(); i++)
		{
			if (m_models[i]->getDestroy())
			{
				ms = m_models[i];
				m_MapModels.erase((Model *)ms);
				m_models.erase(m_models.begin() + i--);
				delete(ms);
			}
		}
		for (int i = 0; i < m_models.size(); i++)
		{
			m_models[i]->setIndexUbo(i);
		}
		for (int i = 0; i < m_modelBuffers.size(); i++)
		{
			if (m_modelBuffers[i]->getDestroy())
			{
				mb = m_modelBuffers[i];
				m_MapModelsBuffers.erase((ShapeBuffer *)mb);
				m_modelBuffers.erase(m_modelBuffers.begin() + i--);
				delete(mb);
			}
		}
		m_vM->str_VulkanDescriptor->modelCount = m_models.size();
	}

	void Model_Manager::MajTexture()
	{
		for (MShape * models : m_models)
		{
			models->MajTexture();
		}
	}

	RayCast * Model_Manager::getRayCast()
	{
		return &m_RayCast;
	}

	ModelBuffer * Model_Manager::CastModelBuffer(ShapeBuffer * sb)
	{
		return m_MapModelsBuffers[sb];
	}
}