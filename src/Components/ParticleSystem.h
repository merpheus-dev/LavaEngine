#pragma once
#include "../Renderer/Particle.h"
#include "../Renderer/ParticleRenderer.h"
#include <vector>
namespace Lava
{
	class ParticleSystem
	{
	public:
		void add_particle(Particle* particle)
		{
			particles.push_back(particle);
		}
		
		void update()
		{
			for (size_t i = 0; i < particles.size(); i++)
			{
				if (!particles[i]->update())
				{
					particles.erase(particles.begin() + i);
				}
			}
		}

	public:
		std::vector<Particle*> particles;

	};
}