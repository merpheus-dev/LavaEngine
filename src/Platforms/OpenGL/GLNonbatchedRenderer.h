#pragma once
#include "../../Renderer/NonbatchedRenderer.h"
namespace Lava {
	namespace OpenGL {
		class GLNonbatchedRenderer : public NonbatchedRenderer {
			// Inherited via NonbatchedRenderer
			virtual void Render(CameraData& data) override;
			virtual void LoadShaders() override;
		};
	}
}