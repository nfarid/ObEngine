#include "SoundManager.hpp"

namespace obe
{
	namespace Sound
	{
		std::map<std::string, sf::SoundBuffer> SoundWrapper::SoundBank = std::map<std::string, sf::SoundBuffer>();
		SoundWrapper::SoundWrapper()
		{
		}

		SoundWrapper::SoundWrapper(const std::string& filename)
		{
			this->load(filename);
		}

		void SoundWrapper::load(const std::string& filename)
		{
			if (SoundBank.find(filename) == SoundBank.end())
			{
				sf::SoundBuffer loadSound;
				System::Path(filename).loadResource(&loadSound, System::Loaders::soundLoader);
				SoundBank[filename] = loadSound;
			}
			m_sound.setBuffer(SoundBank[filename]);
		}

		bool SoundWrapper::isLooping() const
		{
			return m_sound.getLoop();
		}

		void SoundWrapper::setLooping(const bool& looping)
		{
			m_sound.setLoop(looping);
		}

		sf::Time SoundWrapper::getPlayingOffset() const
		{
			return m_sound.getPlayingOffset();
		}

		void SoundWrapper::setPlayingOffset(const sf::Time& offset)
		{
			m_sound.setPlayingOffset(offset);
		}

		float SoundWrapper::getPitch() const
		{
			return m_sound.getPitch();
		}

		void SoundWrapper::setPitch(float pitch)
		{
			m_sound.setPitch(pitch);
		}

		float SoundWrapper::getVolume() const
		{
			return m_sound.getVolume();
		}

		void SoundWrapper::setVolume(float volume)
		{
			m_sound.setVolume(volume);
		}

		void SoundWrapper::setPosition(float x, float y, float z)
		{
			m_sound.setPosition(x, y, z);
		}

		sf::Vector3f SoundWrapper::getPosition() const
		{
			return m_sound.getPosition();
		}

		void SoundWrapper::useSoundPosition(bool usePosition)
		{
			m_sound.setRelativeToListener(usePosition);
		}

		bool SoundWrapper::doesUsesSoundPosition() const
		{
			return m_sound.isRelativeToListener();
		}

		void SoundWrapper::setSpatialAttenuation(float attenuation)
		{
			m_sound.setAttenuation(attenuation);
		}

		float SoundWrapper::getSpatialAttenuation() const
		{
			return m_sound.getAttenuation();
		}

		void SoundWrapper::setMinimumDistance(float distance)
		{
			m_sound.setMinDistance(distance);
		}

		float SoundWrapper::getMinimumDistance() const
		{
			return m_sound.getMinDistance();
		}

		const std::string& SoundWrapper::getStatus() const
		{
			switch (m_sound.getStatus())
			{
			case sf::SoundSource::Stopped: return "Stopped";
			case sf::SoundSource::Paused: return "Paused";
			case sf::SoundSource::Playing: return "Playing";
			}
		}

		void SoundWrapper::pause()
		{
			m_sound.pause();
		}

		void SoundWrapper::play()
		{
			m_sound.play();
		}

		void SoundWrapper::stop()
		{
			m_sound.stop();
		}
	}
}