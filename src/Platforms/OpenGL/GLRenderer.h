#pragma once
#include "../../Renderer/Renderer.h"
#include "GLRenderObject.h"
#include "GLMeshData.h"
#include "GLShader.h"
#include "GLShaderBank.h"
#include<vector>
#include<memory>
namespace Lava {
	namespace OpenGL {
		class GLRenderer :public Renderer {
		public:
			GLRenderer(std::vector<GLShader*> shader_list);
			virtual ~GLRenderer();
			virtual void Update() override;
			void AddRenderObject(GLRenderObject* renderObject)
			{
				m_renderlist.push_back(renderObject);
			}
			void EnableAttributesForRenderObject(int objectIndex) {
				m_renderlist[objectIndex]->EnableAttributes();
			}
			void DisableAttributesForRenderObject(int objectIndex) {
				m_renderlist[objectIndex]->DisableAttributes();
			}
		private:
			void LoadDefaultShader(std::vector<GLShader*>& list);
			std::vector<GLRenderObject*> m_renderlist;
			GLShaderBank* m_bank;
		};
	}
}