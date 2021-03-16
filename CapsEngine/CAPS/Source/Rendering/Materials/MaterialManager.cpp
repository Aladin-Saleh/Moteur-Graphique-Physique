#include "MaterialManager.hpp"

namespace Ge
{
	bool MaterialManager::Initialize(VulkanMisc * vM)
	{
		vulkanM = vM;
		AllocateMaterial();
		Debug::Info("Initialisation du Material Manager");
		return true;
	}

	std::vector<Materials*> MaterialManager::GetMaterial()
	{
		return m_materials;
	}

	Material * MaterialManager::AllocateMaterial()
	{
		Materials * material = new Materials(m_materials.size(), vulkanM);
		m_materials.push_back(material);
		m_MapMaterials[(Material *)material] = material;
		vulkanM->str_VulkanDescriptor->materialCount = m_materials.size();
		return (Material *)material;
	}

	void MaterialManager::DestroyMaterial(Material * material)
	{
		Materials * mat;
		mat = m_MapMaterials[material];
		m_MapMaterials.erase(material);
		m_materials.erase(m_materials.begin() + mat->GetIndex());
		delete(mat);
		m_recreateDescripteur = true;
		vulkanM->str_VulkanDescriptor->materialCount = m_materials.size();
		MajIndex();
	}

	bool MaterialManager::recreateDescripteurMaterial()
	{
		bool buf = m_recreateDescripteur;
		m_recreateDescripteur = false;
		return buf;
	}

	void MaterialManager::UpdateUniformBufferObject()
	{
		for (Materials * material : m_materials)
		{
			material->UpdateUniformBufferMaterial();
		}
	}

	Materials * MaterialManager::GetBaseMaterial()
	{
		return m_materials[0];
	}

	void MaterialManager::Release()
	{
		for (Materials * material : m_materials)
		{
			delete(material);
		}
		m_materials.clear();
		m_MapMaterials.clear();
		Debug::Info("Liberation du Material Manager");
	}

	void MaterialManager::MajIndex()
	{
		for (int i = 0; i < m_materials.size(); i++)
		{
			m_materials[i]->SetIndex(i);
		}
	}
}