#pragma once
#include "../../Renderer/PostProcessingEffect.h"
#include "GLShaderBank.h"
#include "../../Core/WindowManager.h"
namespace Lava {
	namespace OpenGL {
		class GLPostProcessingEffect : public PostProcessingEffect {
		public:
			GLPostProcessingEffect(const char* shader)
				: PostProcessingEffect(),
				m_bank(nullptr),
				shaderPath(shader) 
			{
				Init();
			};
			virtual void Init() override;
			virtual void Render(unsigned int baseColorTargetId, bool last) override;
		protected:
			GLShaderBank* m_bank;
			const char* shaderPath;
		};
	}
}