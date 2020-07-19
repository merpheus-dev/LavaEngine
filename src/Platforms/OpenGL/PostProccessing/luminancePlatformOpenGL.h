#pragma once
#include "../GLPostProcessingEffect.h"
namespace Lava {
	namespace OpenGL {
		class BlurFX : public GLPostProcessingEffect {
		public:
			BlurFX( bool horizontal ) : GLPostProcessingEffect( "Shaders/gaussian.fp" )
			{
				m_bank->GetShader( 1 )->SetBool( "horizontal" , horizontal );
			};
		};
	}
}