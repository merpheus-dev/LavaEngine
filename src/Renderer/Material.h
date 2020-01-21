#pragma once
#include <array>
#include "Texture.h"
namespace Lava {
	//To-Do: All those stuff should be in an array to support multiple
	//Textures colors and texcoords for shaders
	struct Material {
		Texture* m_mainTexture;
		float m_tintColor[3];
		float* m_uvCoords;
		int m_uvCoordCount;
	};
}