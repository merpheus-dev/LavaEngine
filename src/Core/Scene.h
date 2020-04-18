#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <array>
#include "SceneObjectInfo.h"
#include "../Components/Camera.h"
#include "../Core/Data/SceneData.h"
namespace Lava {
	class Scene {
	public:
		Scene();
		Scene(DataContainers::SceneData* _scene_data) : scene_data(_scene_data){};
		void Load(const char* fileDir);

	private:
		void LoadModelInfos(std::string sceneContext);

	public:
		DataContainers::SceneData* scene_data;
		std::vector<SceneObjectInfo> SceneObjects;
		Camera* ActiveCamera;
	};
}