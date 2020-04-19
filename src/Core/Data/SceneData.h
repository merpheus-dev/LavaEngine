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

			std::vector<const char*> skybox_textures = {
				"Assets/sky/right.png","Assets/sky/left.png","Assets/sky/top.png","Assets/sky/bottom.png","Assets/sky/back.png","Assets/sky/front.png"
			};
		};
	}
}
