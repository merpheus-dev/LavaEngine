#pragma once
#include "../../Renderer/EntityRenderer.h"
#include "GLShader.h"

namespace Lava
{
	namespace OpenGL
	{
		class GLStandardRenderer : public EntityRenderer
		{
		public:
			GLStandardRenderer(Scene* scene, std::vector<GLShader*> shader_list);
			~GLStandardRenderer();
			void Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
			void CompleteRender() override;
			void Update(Scene* scene) override;
			void BindAttribute(int variableIndex, const char* variableName) override;
			void SetLightInfo(Scene* scene) override;
			void SetFogInfo() override;
			void PushInstanceData(Entity* entityPtr) override;
			void BindObjects(Entity* entityPtr) override;
			void UnBindObjects(Entity* entityPtr) override;
			void Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities, glm::vec4 clipPlane) override;
			void AddRenderObject(Entity* entity)
			{
				m_renderlist.push_back(entity);
			}
		private:
			void LoadDefaultShader(std::vector<GLShader*>& list);
			std::map<MeshRenderer*, std::vector<Entity*>*> dummy_render_parameter;
			std::vector<Entity*> m_renderlist;
			GLShaderBank* m_bank;
		};
	}
}
