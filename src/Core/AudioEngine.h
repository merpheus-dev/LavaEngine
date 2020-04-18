#pragma once
#include "soloud.h"
#include "soloud_wav.h"
namespace Lava
{
	class AudioEngine
	{
	public:
		static SoLoud::Soloud*& GetEngine()
		{
			if (!backend)
				backend = new SoLoud::Soloud();
			return backend;
		}
		void Setup()
		{
			GetEngine()->init();
		}
		void Disable()
		{
			GetEngine()->deinit();
		}
		
		void Update()
		{
			GetEngine()->update3dAudio();
		}
		
	private:
		static SoLoud::Soloud* backend;
	};
}