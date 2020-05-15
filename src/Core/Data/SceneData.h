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
				"Assets/sky/right2.png","Assets/sky/left2.png","Assets/sky/top2.png","Assets/sky/bottom2.png","Assets/sky/back2.png","Assets/sky/front2.png"
			};
		};
	}
}
