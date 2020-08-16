#pragma once
#include "GLBloomPostProcess.h"
namespace Lava {
	namespace OpenGL {
		class BloomFX : public GLBloomPostProcess {
		public:
			BloomFX() : GLBloomPostProcess( "Shaders/bloom.fp" )
			{
				//m_bank->GetShader( 1 )->SetBool( "horizontal" , horizontal );
			};
		};
	}
}