#pragma once
#include "../GLPostProcessingEffect.h"
namespace Lava {
	namespace OpenGL {
		class HdrFX : public GLPostProcessingEffect {
		public:
			HdrFX() : GLPostProcessingEffect("Shaders/hdr.fp") {};
		};
} }