#pragma once
#include <glm.hpp>
namespace Lava {
	class Light {
	public:
		glm::vec3 Position;
		glm::vec3 Color;
		float Intensity;
		glm::vec3 Attenuation;
		Light(glm::vec3 color = glm::vec3(0))
			:Position(glm::vec3(0)), Color(color), Intensity(0.0f), Attenuation(glm::vec3(1, 0, 0))
		{
		}
	};

	class DirectionalLight : public Light {
	public:
		DirectionalLight(glm::vec3 color = glm::vec3(1)) : Light(color)
		{

		}
	};

	class PointLight : public Light {
	public:
		PointLight(glm::vec3 attenuation = glm::vec3(1, 0.01f, 0.002f))
		{
			Attenuation = attenuation;
		}
	};
}