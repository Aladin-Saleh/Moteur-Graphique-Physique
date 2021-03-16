#include "SoundBufferManager.hpp"

namespace Ge
{
	void SoundBufferManager::Register(const std::string& bufferKey, SoundBuffer * buffer){
		m_bufferIDs.insert(Couple(bufferKey, buffer));
		m_bufferV.push_back(buffer);
	}

	void SoundBufferManager::Unregister(const std::string& bufferKey) {
		SoundBuffer * sb = m_bufferIDs[bufferKey];
		m_bufferIDs.erase(bufferKey);
		for (int i = 0; i < m_bufferV.size(); i++)
		{
			if (sb == m_bufferV[i])
			{
				m_bufferV.erase(m_bufferV.begin() + i);
				break;
			}
		}
		delete(sb);
	}

	SoundBuffer * SoundBufferManager::GetBuffer(const std::string& bufferKey){
		return m_bufferIDs[bufferKey];
	}

	void SoundBufferManager::Release()
	{
		for (SoundBuffer * sb : m_bufferV)
		{
			delete(sb);
		}
	}

}