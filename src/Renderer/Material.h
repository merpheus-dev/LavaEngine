#pragma once
#include <array>
#include "Texture.h"
#include <vector>
namespace Lava {
	//To-Do: All those stuff should be in an array to support multiple
	//Textures colors and texcoords for shaders
	struct Material {
		Texture* m_mainTexture;
		float m_tintColor[3];
		float shininess = 1;
		float glossDamping = 10;
	};
}