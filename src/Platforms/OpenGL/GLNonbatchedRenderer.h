#pragma once
#include "../../Renderer/NonbatchedRenderer.h"
#include "GLShaderBank.h"
namespace Lava {
	namespace OpenGL {
		class GLNonbatchedRenderer : public NonbatchedRenderer {
			virtual void Setup(Scene* scene);
			virtual void Render(CameraData& data) override;
			virtual void PrepareFrameData(CameraData& data) override;
			virtual ~GLNonbatchedRenderer();

		private:
			GLShaderBank* m_bank;

			// Inherited via NonbatchedRenderer
			virtual void BindObject(Entity* entity) override;

			// Inherited via NonbatchedRenderer
			virtual void EnableAttributesForRenderObject(Entity* entity) override;
			virtual void DisableAttributesForRenderObject(Entity* entity) override;

			// Inherited via NonbatchedRenderer
			virtual void UnbindObject(Entity* entity) override;
		};
	}
}