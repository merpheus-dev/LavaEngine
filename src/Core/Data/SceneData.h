#pragma once
#include "../../Components/Light.h"

namespace Lava
{
	namespace DataContainers
	{
		struct SceneData
		{
			glm::vec3 fog_color;
			float fog_density = 0.f;

			std::array<Light*, 4>* lights;
			float ambient_light_intensity = .2f;
		};
	}
}
