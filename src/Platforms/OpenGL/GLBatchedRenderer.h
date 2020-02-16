#pragma once
#include "../../Renderer/BatchedRenderer.h"
#include "GLShader.h"
#include "GLRenderer.h"
namespace Lava {
	namespace OpenGL {
		class GLBatchedRenderer : public BatchedRenderer{
		public:
			GLBatchedRenderer(Scene* scene,std::vector<GLShader*> shader_list);
			virtual ~GLBatchedRenderer();
			virtual void Update(Scene* scene) override;
			virtual void AddToBatch(Entity* entity) override;
		};
	}
}