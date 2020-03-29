#include "GLBatchedRenderer.h"
namespace Lava {
	namespace OpenGL {
		GLBatchedRenderer::GLBatchedRenderer(Scene* scene,std::vector<GLShader*> shader_list)
		{
			m_renderer = new GLRenderer(scene,shader_list);
			m_renderer->BindAttribute(0, "position");
			m_renderer->BindAttribute(1, "texCoord");
			m_renderer->BindAttribute(2, "normal");
			m_renderer->BindAttribute(3, "tangent");
		}

		GLBatchedRenderer::~GLBatchedRenderer()
		{
			delete m_renderer;
		}

		void GLBatchedRenderer::Update(Scene* scene, glm::vec4 clipPlane)
		{
			m_renderer->Configure(scene->ActiveCamera->GetViewMatrix(), scene->ActiveCamera->GetProjectionMatrix());
			m_renderer->SetLightInfo(scene);
			m_renderer->SetFogInfo();
			m_renderer->Render(m_batchList,clipPlane);
			m_renderer->CompleteRender();
			m_batchList.clear();
		}

		void GLBatchedRenderer::AddToBatch(Entity* entity)
		{
			bool didRendererBatched = m_batchList.find(entity->meshRenderer) != m_batchList.end();
			if (!didRendererBatched) {
				auto meshRenderer = entity->GetMeshRenderer(Platform::OpenGL);
				meshRenderer->GetRenderObject();
				std::vector<Entity*>* entityList = new std::vector<Entity*>();
				entityList->push_back(entity);
				m_batchList.insert(std::pair<MeshRenderer*, std::vector<Entity*>*>(meshRenderer, entityList));
			}
			else {
				auto found = m_batchList.at(entity->meshRenderer);
				found->push_back(entity);
			}
		}
	}
}
