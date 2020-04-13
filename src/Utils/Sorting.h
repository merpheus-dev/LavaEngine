#pragma once
#include <vector>
#include "../Renderer/Particle.h"

namespace Lava
{
	class Sorting
	{
	public:
		static void sort_particles(std::vector<Particle*>& particles)
		{
			if (particles.size() < 1) return;
			for(auto i=1;i<particles.size()-1;i++)
			{
				const auto current = particles.at(i);
				auto j = i - 1;
				while(j>=0 && particles.at(j)->camera_distance>current->camera_distance)
				{
					particles.at(j + 1) = particles.at(j);
					j--;
				}
				particles.at(j + 1) = current;
			}
		}
	};
}
