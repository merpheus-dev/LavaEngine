#pragma once
#include "../../Renderer/Renderer.h"
#include "../../Components/Entity.h"
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
			virtual void Update(Camera camera,Light light) override;
			virtual void BindAttribute(int variableIndex, const char* variableName) override;
			void AddRenderObject(Entity* renderObject)
			{
				m_renderlist.push_back(renderObject);
			}
			void EnableAttributesForRenderObject(int objectIndex) {
				((GLRenderObject*)(m_renderlist[objectIndex]->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))
					->EnableAttributes();
			}
			void DisableAttributesForRenderObject(int objectIndex) {
				((GLRenderObject*)(m_renderlist[objectIndex]->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))
					->DisableAttributes();
			}

			glm::mat4 GetProjectionMatrix() {
				return glm::perspective<float>(glm::radians(70.0), 1.0, .001, 1000.);
			}

			glm::mat4 GetViewMatrix(Camera& camera) {
				return glm::lookAt<float>(camera.transform.Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			}
		private:
			void LoadDefaultShader(std::vector<GLShader*>& list);
			std::vector<Entity*> m_renderlist;
			GLShaderBank* m_bank;
		};
	}
}