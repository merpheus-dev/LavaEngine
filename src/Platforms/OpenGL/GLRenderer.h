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
			virtual void Configure(glm::mat4 viewMatrix,glm::mat4 projectionMatrix) override;
			virtual void SetLightInfo(Light& light) override;
			virtual void SetFogInfo() override;
			virtual void CompleteRender() override;
			virtual void PushInstanceData(Entity* entityPtr) override;
			virtual void BindObjects(Entity* entityPtr) override;
			virtual void UnBindObjects(Entity* entityPtr) override;
			virtual void Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities) override;
			virtual void Update(Camera camera,Light light) override;
			virtual void BindAttribute(int variableIndex, const char* variableName) override;
			void AddRenderObject(Entity* renderObject)
			{
				m_renderlist.push_back(renderObject);
			}
			void EnableAttributesForRenderObject(Entity* entity) {
				((GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))
					->EnableAttributes();
			}
			void DisableAttributesForRenderObject(Entity* entity) {
				((GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))
					->DisableAttributes();
			}

		private:
			void LoadDefaultShader(std::vector<GLShader*>& list);
			std::vector<Entity*> m_renderlist;
			GLShaderBank* m_bank;
			glm::vec3 FogColor = glm::vec3(.2, 0.2, .2);
			float FogDensity = .8;
		};
	}
}