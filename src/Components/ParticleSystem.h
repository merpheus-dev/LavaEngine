#pragma once
#include "../Renderer/Particle.h"
#include "../Renderer/ParticleRenderer.h"
#include <vector>
#include <glm.hpp>
#include <gtc/random.hpp>
namespace Lava
{
	class ParticleSystem
	{
	public:
		void generate_particles(glm::vec3 center)
		{
			auto count = static_cast<int>(glm::floor(emission_rate * Time::deltaTime));
			auto rand = glm::linearRand(0, count);
			count = count + static_cast<int>(randomize_count ? rand : 0.f) + emission_rate;
			for(auto i=0;i<count;i++)
			{
				emit_particle(center);
			}
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
	private:
		void emit_particle(glm::vec3 center)
		{
			const auto x = glm::linearRand(0.f, 1.f) * 2.f - 1.f;
			const auto y = glm::linearRand(0.f, 1.f) * 2.f - 1.f;
			const auto velocity = glm::normalize(glm::vec3(x, 1, y)) * speed;
			particles.push_back(new Particle(center, glm::vec3(0), glm::vec3(.1),
				velocity, gravity_effect, life_length));
		}
		
	public:
		std::vector<Particle*> particles;
		
	public:
		float emission_rate;
		float speed;
		float gravity_effect;
		float life_length;
		bool randomize_count;
	};
}