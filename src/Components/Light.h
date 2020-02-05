#pragma once
#include <glm.hpp>
namespace Lava {
	class Light {
	public:
		glm::vec3 Position;
		glm::vec3 Color;
		float Intensity;
		Light(glm::vec3 color = glm::vec3(1))
			:Position(glm::vec3(1)),Color(color),Intensity(1.0f)
		{
		}
	};
}