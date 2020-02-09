#pragma once
#include <glm.hpp>
struct SceneObjectInfo {
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

struct ModelObjectInfo : SceneObjectInfo {
	const char* modelPath;
	const char* texturePath;
};