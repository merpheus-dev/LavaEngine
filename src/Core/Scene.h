#pragma once
#include <vector>
#include <glm.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include "SceneObjectInfo.h"
#include "../Utils/TextUtils.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
namespace Lava {
	class Scene {
	public:
		Scene();
		void Load(const char* fileDir);

	private:
		void LoadModelInfos(std::string sceneContext);

	public:
		std::vector<SceneObjectInfo> SceneObjects;
		Camera* ActiveCamera;

		glm::vec3 FogColor;
		float FogDensity = 0.f;

		std::array<Light*, 4>* Lights;
		float AmbientLightIntensity = .2f;
	};
}