#pragma once
#include "../src/Core/GameLayer.h"
#include "../src/Core/InputManager.h"
#include "../src/Components/Camera.h"
#include "../src/Core/LavaTime.h"

namespace Lava
{
	namespace Demo
	{
		class CameraController
		{
		public:
			static void Update(Camera* camera)
			{
				if (InputManager::GetKeyPress(GLFW_KEY_J))
				{
					camera->transform.Rotation.y -= Time::deltaTime * 100;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_K))
				{
					camera->transform.Rotation.y += Time::deltaTime * 100;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_W))
				{
					camera->transform.Position.z -= Time::deltaTime;
					std::cout << Time::deltaTime << std::endl;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_S))
				{
					camera->transform.Position.z += Time::deltaTime;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_A))
				{
					camera->transform.Position.x -= Time::deltaTime;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_D))
				{
					camera->transform.Position.x += Time::deltaTime;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_Q))
				{
					camera->transform.Position.y -= Time::deltaTime;
				}
				if (InputManager::GetKeyPress(GLFW_KEY_E))
				{
					camera->transform.Position.y += Time::deltaTime;
				}
			}
		};
	}
}
