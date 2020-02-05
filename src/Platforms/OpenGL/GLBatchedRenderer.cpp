#include "GLBatchedRenderer.h"
namespace Lava {
	namespace OpenGL {
		GLBatchedRenderer::GLBatchedRenderer(std::vector<GLShader*> shader_list)
		{
			m_renderer = new GLRenderer(shader_list);
			m_renderer->BindAttribute(0, "position");
			m_renderer->BindAttribute(1, "texCoord");
			m_renderer->BindAttribute(2, "normal");
		}

		GLBatchedRenderer::~GLBatchedRenderer()
		{
			delete m_renderer;
		}

		void GLBatchedRenderer::Update(Camera camera, Light light)
		{
			m_renderer->Configure(GetViewMatrix(camera),GetProjectionMatrix(camera));
			m_renderer->SetLightInfo(light);
			m_renderer->SetFogInfo();
			m_renderer->Render(m_batchList);
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
