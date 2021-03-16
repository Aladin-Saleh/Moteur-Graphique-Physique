#include "AudioSource.hpp"

namespace Ge
{

	AudioSource::AudioSource(SoundBufferManager * sM) 
	{
		m_sourceID = 0;
		m_bLoop = false;
		m_volume = 1.0f;
		m_pitch = 1.0f;
		m_position = Vector3(0.0f, 0.0f, 0.0f);
		m_velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_soundBufferManager = sM;
	}

	AudioSource::~AudioSource() 
	{
		alDeleteSources(1, &m_sourceID);
	}

	void AudioSource::Play() {
		//Debug::Info("AudioSource: Play");
		alSourcei(m_sourceID, AL_BUFFER, m_buffer->GetID());
		alSourcePlay(m_sourceID);
	}

	void AudioSource::Stop() {
		//Debug::Info("AudioSource: STOP");
		alSourceStop(m_sourceID);
	}

	void AudioSource::Pause() {
		//Debug::Info("AudioSource: PAUSE");
		alSourcePause(m_sourceID);
	}

	void AudioSource::SetLooping(bool bLoop) {
		m_bLoop = bLoop;
		alSourcei(m_sourceID, AL_LOOPING,m_bLoop);
	} 

	void AudioSource::SetVolume(float volume) {
		m_volume = volume;
		alSourcef(m_sourceID, AL_GAIN, m_volume);
	}

	void AudioSource::SetPitch(float pitch) {
		m_pitch = pitch;
		alSourcef(m_sourceID, AL_PITCH, m_pitch);
	}

	void AudioSource::setPosition(Vector3 pos) 
	{
		ALfloat SourcePos[] = { pos.x, pos.y, pos.z };
		m_transform.position.x = pos.x;
		m_transform.position.y = pos.y;
		m_transform.position.z = pos.z;
		m_transform.pos = pos;
		alSourcefv(m_sourceID, AL_POSITION, SourcePos);
	}

	void AudioSource::SetVelocity(Vector3 velocity) {
		ALfloat SourceVel[] = { velocity.x, velocity.y, velocity.z };
		alSourcefv(m_sourceID, AL_VELOCITY, SourceVel);
	}

	void AudioSource::SetSoundBuffer(const char* bufferID) {
		alGenSources(1, &m_sourceID);
		m_buffer = m_soundBufferManager->GetBuffer(bufferID);
		alSourcei(m_sourceID, AL_BUFFER, m_buffer->GetID());
	}

	bool AudioSource::IsPlaying() const {
		ALenum state;        
		alGetSourcei(m_sourceID, AL_SOURCE_STATE, &state);        
		return (state == AL_PLAYING);
	}

	bool AudioSource::IsLooping() const {
		return m_bLoop;
	}

	float AudioSource::GetVolume() const {
		return m_volume;
	}

	float AudioSource::GetPitch() const {
		return m_pitch;
	}

	void AudioSource::OnGUI()
	{
		GObject::OnGUI();
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "AudioSource\n");
		if (ImGui::Combo("ActivationState", &style_idx, "Play\0Pause\0Stop\0"))
		{
			switch (style_idx)
			{
			case 0: AudioSource::Play(); break;
			case 1: AudioSource::Pause(); break;
			case 2: AudioSource::Stop(); break;
			}
		}
		if (ImGui::DragFloat("Volume", &m_volume,0.1f))
		{
			AudioSource::SetVolume(m_volume);
		}
		if (ImGui::DragFloat("Pitch", &m_pitch,0.1f))
		{
			AudioSource::SetPitch(m_pitch);
		}
		if (ImGui::Checkbox("Looping", &m_bLoop))
		{
			AudioSource::SetLooping(m_bLoop);
		}
	}

	Vector3 AudioSource::getPosition() 
	{
		return m_position;
	}

	Vector3 AudioSource::GetVelocity() const {
		return m_velocity;
	}


}