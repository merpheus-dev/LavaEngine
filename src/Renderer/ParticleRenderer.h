#pragma once
#include "BaseRenderer.h"
namespace Lava
{
	class ParticleRenderer :public BaseRenderer
	{
	public:
		ParticleRenderer(Scene* scene):BaseRenderer(scene){}
		virtual ~ParticleRenderer() = default;
		virtual void Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
		virtual void Update(Scene* scene) = 0;
		virtual void LoadShaders() = 0;
	protected:
		float* m_vertices = new float[8] { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	};
}