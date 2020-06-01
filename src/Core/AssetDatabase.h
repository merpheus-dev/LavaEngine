#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "../Renderer/Texture.h"
#include "../Renderer/TextureCubeMap.h"
#include "../Utils/Debug.h"
#include <vector>
#include <string>
namespace Lava {
	class AssetDatabase {
	public:
		static Texture* LoadTexture(const char* file_name, int component_count = 0, bool repeat = false);
		static int LoadCubeMap(std::vector<const char*> cubeMapFiles);
	};
}