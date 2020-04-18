#pragma once
#include "soloud.h"
#include "soloud_wav.h"
namespace Lava
{
	class AudioEngine
	{
	public:
		static SoLoud::Soloud& GetEngine()
		{
			return backend;
		}
		void Setup()
		{
			backend.init();
		}
		void Disable()
		{
			backend.deinit();
		}
		
		void Update()
		{
			backend.update3dAudio();
		}
		
	private:
		static SoLoud::Soloud backend;
	};
}