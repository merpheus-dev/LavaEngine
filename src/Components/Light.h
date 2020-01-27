#pragma once
#include <glm.hpp>
namespace Lava {
	struct Light {
		glm::vec3 Position;
		glm::vec3 Color;
		Light(glm::vec3 color = glm::vec3(1))
			:Position(glm::vec3(1)),Color(color)
		{
		}
	};
}