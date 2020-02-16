#pragma once
#include "BaseRenderer.h"
namespace Lava {
	class SkyboxRenderer :public BaseRenderer{
	public:
		SkyboxRenderer(Scene* scene) : BaseRenderer(scene) {}
		virtual void LoadShaders() = 0;
	};
}