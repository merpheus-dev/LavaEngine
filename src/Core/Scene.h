#pragma once
#include <vector>
#include <glm.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "../Utils/TextUtils.h"
#include "SceneObjectInfo.h"
namespace Lava {
	class Scene {
	public:
		std::vector<SceneObjectInfo> SceneObjects;
		glm::vec3 FogColor;
		float FogDensity = 0.f;
	public:
		void Load(const char* fileDir);

	private:
		void LoadModelInfos(std::string sceneContext);
	};
}