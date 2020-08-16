#pragma once
#include "../../../Renderer/PostProcessingEffect.h"
#include "../GLShaderBank.h"
#include "../../../Core/WindowManager.h"
namespace Lava {
	namespace OpenGL {
		class GLBloomPostProcess : public PostProcessingEffect {
		public:
			GLBloomPostProcess(const char* shader)
				: PostProcessingEffect(),
				m_bank(nullptr),
				shaderPath(shader) 
			{
				Init();
			};
			virtual void Init() override;
			virtual void Render(unsigned int renderTargets[], bool last) override;
		protected:
			GLShaderBank* m_bank;
			GLShaderBank* blurBank;
			const char* shaderPath;
			unsigned int pingPongFbos[2];
			unsigned int pingPongTextures[2];
		};
	}
}