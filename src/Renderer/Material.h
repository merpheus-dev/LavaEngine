#pragma once
#include <array>
#include "Texture.h"
#include <vector>
#include <glm.hpp>
namespace Lava {
	//To-Do: All those stuff should be in an array to support multiple
	//Textures colors and texcoords for shaders
	struct Material {
		Texture* m_mainTexture;
		Texture* m_nrmTexture;
		Texture* emissionMap;
		glm::vec3 albedoColor;
		float* uvCoords;
		unsigned int uvCoordCount;

		bool castShadows = 0;
		bool receiveShadows = 1;
		float m_tintColor[3];
		float shininess = 1;
		float glossDamping = 10;
	};
}