#pragma once
#include "../../Renderer/Renderer.h"
#include "GLRenderObject.h"
#include "GLMeshData.h"
#include<vector>
#include<memory>
namespace Lava {
	namespace OpenGL {
		class GLRenderer :public Renderer {
		public:
			GLRenderer();
			virtual ~GLRenderer();
			virtual void Update() override;
			void AddRenderObject(GLRenderObject* renderObject)
			{
				m_renderlist.push_back(renderObject);
			}
		private:
			std::vector<GLRenderObject*> m_renderlist;
		};
	}
}