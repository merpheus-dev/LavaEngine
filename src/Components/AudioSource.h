#pragma once
#include "../Core/AudioEngine.h"
#include "../Components/Transform.h"
namespace Lava
{
	class AudioSource
	{
	public:
		AudioSource()
		{
			audio_source = new SoLoud::Wav();
		}
		void SetClip(const char* _clip)
		{
			audio_source->load(_clip);
			clip = _clip;
		}

		void Play()
		{
			auto engine = AudioEngine::GetEngine();
			if (!is3d)
			{
				handle = engine->play(*audio_source, volume, 0, pause);
			}
			else
			{
				handle = engine->play3d(*audio_source, transform.Position.x, transform.Position.y, transform.Position.z);
			}
			engine->setLooping(handle, isLooping);
		}

	public:
		Transform transform;
		float volume = 1;
		bool is3d = false;
		bool pause = false;
		bool isLooping = false;
		int handle;
	private:
		SoLoud::Wav* audio_source;
		const char* clip;
	};
}
