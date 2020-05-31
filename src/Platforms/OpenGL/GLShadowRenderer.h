#pragma once
#include "../../Renderer/NonbatchedRenderer.h"
#include "GLShaderBank.h"
#include "GLShadowMap.h"
namespace Lava {
	namespace OpenGL {
		class GLShadowRenderer : public NonbatchedRenderer{
		public:
			virtual void Setup(Scene* scene) override;
			virtual void Render(CameraData& data) override;
			virtual void PrepareFrameData(CameraData& data) override;
			virtual ~GLShadowRenderer();
		private:
			virtual void BindObject(Entity* entity) override;
			virtual void UnbindObject(Entity* entity) override;
			virtual void EnableAttributesForRenderObject(Entity* entity) override;
			virtual void DisableAttributesForRenderObject(Entity* entity) override;
		public:
			float size = 10.f;
			float near_plane = 0.1f;
			float far_plane = 7.5f;
			GLShadowMap* m_shadowMap;
			glm::mat4 lightSpaceMatrix;
		private:
			GLShaderBank* m_bank;
		};
	}
}