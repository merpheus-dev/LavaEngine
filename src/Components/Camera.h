#pragma once
#include "Transform.h"
#include "../Core/WindowManager.h"
#include <glm.hpp>
namespace Lava {
	class Camera {
	public:
		Transform transform;
		float fov = 70.f;
		float near_plane = 0.001f;
		float far_plane = 1000.0f;
	public:
		glm::mat4 GetProjectionMatrix() {
			return glm::perspective<float>(glm::radians(fov), WindowManager::GetAspectRatio(), near_plane, far_plane);
		}

		glm::mat4 GetViewMatrix() {
			glm::vec3 direction;
			direction.x = cos(glm::radians(transform.Rotation.y)) * cos(glm::radians(transform.Rotation.x));
			direction.y = sin(glm::radians(transform.Rotation.x));
			direction.z = sin(glm::radians(transform.Rotation.y)) * cos(glm::radians(transform.Rotation.x));
			return glm::lookAt<float>(transform.Position, transform.Position + glm::normalize(direction), glm::vec3(0, 1, 0));
		}
	};
}