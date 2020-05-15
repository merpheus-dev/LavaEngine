#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <array>
#include "SceneObjectInfo.h"
#include "../Components/Camera.h"
#include "../Core/Data/SceneData.h"
#include "../Components/Entity.h"
#include <tinyxml2.h>
namespace Lava {
	class Scene {
	public:
		Scene(const char* file_name);
		//Scene(DataContainers::SceneData* _scene_data) : scene_data(_scene_data){};
	private:
		void LoadScene();
		void LoadLights();
		void LoadFogData();
		void LoadCamera();
		void LoadBatchedEntities();
		void LoadSeparateEntities();
		void LoadParticleSystems();
	private:
		const char* m_scene_file_name;
		tinyxml2::XMLDocument scene_parser;
		glm::vec3 parse_vector3(const char* text) const;
	public:
		DataContainers::SceneData* scene_data;
		//No active usage yet.
		std::vector<SceneObject*> SceneObjects;
		Camera* ActiveCamera;
	};
}