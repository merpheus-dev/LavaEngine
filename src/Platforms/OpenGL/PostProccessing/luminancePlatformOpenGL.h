#pragma once
#include "../GLPostProcessingEffect.h"
namespace Lava {
	namespace OpenGL {
		class LuminanceFX : public GLPostProcessingEffect {
		public:
			LuminanceFX() : GLPostProcessingEffect("Shaders/colorChanger.fp") {};
		};
	}
}