#pragma once
#include<vector>
#include<memory>
#include "../../Renderer/EntityRenderer.h"
#include "../../Components/Entity.h"
#include "GLRenderObject.h"
#include "GLShader.h"
#include "GLShaderBank.h"
#include "../../Core/Scene.h"
namespace Lava {
	namespace OpenGL {
		class GLRenderer :public EntityRenderer {
		public:
			GLRenderer(Scene* scene, std::vector<GLShader*> shader_list);
			virtual ~GLRenderer();
			virtual void Configure(glm::mat4 viewMatrix,glm::mat4 projectionMatrix) override;
			virtual void SetLightInfo(Scene* scene) override;
			virtual void SetFogInfo() override;
			virtual void CompleteRender() override;
			virtual void PushInstanceData(Entity* entityPtr) override;
			virtual void BindObjects(Entity* entityPtr) override;
			virtual void UnBindObjects(Entity* entityPtr) override;
			virtual void Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities) override;
			virtual void Update(Scene* scene) override;
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
		};
	}
}