#pragma once
#include "../../Renderer/ParticleRenderer.h"
#include "GLShaderBank.h"
#include "../../Renderer/Particle.h"
#include "../../Components/ParticleSystem.h"
namespace Lava
{
	namespace OpenGL
	{
		class GLParticleRenderer : public ParticleRenderer
		{
		public:
			GLParticleRenderer(Scene* scene);
			virtual ~GLParticleRenderer();
			void AttachParticleSystem(ParticleSystem* particle_system);
			void Update(Scene* scene) override;
		private:
			void Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
			void CompleteRender() override;
			void LoadShaders() override;

		private:
			void RenderInternal();
		private:
			std::vector<ParticleSystem*> m_systems;
		private:
			GLShaderBank* m_bank;
			VertexBufferElement* m_bufferLayout;
			GLVAO* m_vao;
			std::shared_ptr<GLVertexBuffer> m_vbo;
		};
	}
}
