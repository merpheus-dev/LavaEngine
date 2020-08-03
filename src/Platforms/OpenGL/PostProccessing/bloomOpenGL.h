#pragma once
#include "../GLPostProcessingEffect.h"
namespace Lava {
	namespace OpenGL {
		class BloomFX : public GLPostProcessingEffect {
		public:
			BloomFX( bool horizontal ) : GLPostProcessingEffect( "Shaders/bloom.fp" )
			{
				m_bank->GetShader( 1 )->SetBool( "horizontal" , horizontal );
			};
		};
	}
}