#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Renderer/MeshMaterialPack.h"
#include <iostream>
namespace Lava {
	namespace Importers {
		class AssetImporter {
		public:
			static MeshMaterialPack* Load(const char* filePath);
		};
	}
}