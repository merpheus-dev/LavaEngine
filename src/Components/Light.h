#pragma once
#include <glm.hpp>
namespace Lava {
	struct Light {
		glm::vec3 Position;
		glm::vec3 Color;
		Light()
			:Position(glm::vec3(0)),Color(glm::vec3(1))
		{

		}
	};
}