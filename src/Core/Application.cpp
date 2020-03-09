#include "Application.h"
#include "WindowManager.h"
#include "../Platforms/OpenGL/GLRenderer.h"
#include "../Platforms/OpenGL/GLMasterRenderer.h"
#include "../Platforms/OpenGL/GLRenderObject.h"
#include "../Renderer/Mesh.h"
#include "../Platforms/OpenGL/GLShader.h"
#include "../Platforms/OpenGL/GLShaderBank.h"
#include "../Core/AssetDatabase.h"
#include "../Components/Entity.h"
#include "../Components/Camera.h"
#include <iterator>
#include <vector>
#include <iostream>
#include "../Utils/ObjImporter.h"
#include "../Utils/AssetImporter.h"
#include "LavaTime.h"
#include <time.h>
#include "../Utils/Mathematics.h"
namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;

		Camera* camera = new Camera();
		Light* light = new DirectionalLight(glm::vec3(.4, .4, .4));

		Scene* scene = new Scene();
		scene->FogColor = glm::vec3(.3, .3, .3);
		scene->FogDensity = .5f;
		scene->Lights->at(0) = light;
		scene->ActiveCamera = camera;

		Lava::OpenGL::GLMasterRenderer _renderer = Lava::OpenGL::GLMasterRenderer(scene);

		std::vector<VertexBufferElement> bufferElements(4);
		bufferElements[0].uniform_name = "position";
		bufferElements[0].uniform_count = 3;
		bufferElements[1].uniform_name = "texCoord";
		bufferElements[1].uniform_count = 2;
		bufferElements[2].uniform_name = "normal";
		bufferElements[2].uniform_count = 3;
		bufferElements[3].uniform_name = "tangent";
		bufferElements[3].uniform_count = 3;

		auto pack = Lava::Importers::AssetImporter::Load("Assets/barrel.obj");
		auto texture = AssetDatabase::LoadTexture("Assets/barrel.png",4);
		auto normal_map = AssetDatabase::LoadTexture("Assets/barrelNormal.png", 4);

		std::vector<Entity*> entities;
		MeshRenderer* batchableRenderer = nullptr;
		for (int a = 0; a < 10; a++) {
			Entity* entity = new Entity(glm::vec3(0., -.5, 0), pack);
			entity->SetBufferLayout(bufferElements);
			entity->material->m_mainTexture = &texture;
			entity->material->m_nrmTexture = &normal_map;
			if (!batchableRenderer)
				batchableRenderer = entity->GetMeshRenderer(Platform::OpenGL);
			else
				entity->meshRenderer = batchableRenderer;
			entities.push_back(entity);
		}


		bool onStartExecuted = false;

		while (!manager.IsWindowClosed()) {
			Time::CalculateDeltaTime();
			if (!onStartExecuted) {
				for (auto& eachEntity : entities) {
					for (int i = 0; i < 3; i++) {
						
						float randPos = Lava::Mathematics::GetRandom() / 50.f;
						eachEntity->transform->Position[i] = randPos;
					}
				}
				onStartExecuted = true;
			}
			for (auto& entity : entities) {
				_renderer.batchedRenderer->AddToBatch(entity);
			}

	#pragma region Debug Input Handling
			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_J) == GLFW_PRESS)
			{
				camera->transform.Rotation.y -= Time::deltaTime*100;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_K) == GLFW_PRESS)
			{
				camera->transform.Rotation.y += Time::deltaTime*100;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
			{
				camera->transform.Position.z -= Time::deltaTime;
				std::cout << Time::deltaTime << std::endl;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
			{
				camera->transform.Position.z +=  Time::deltaTime;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
				camera->transform.Position.x -= Time::deltaTime;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
				camera->transform.Position.x +=  Time::deltaTime;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
				camera->transform.Position.y -=  Time::deltaTime;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_E) == GLFW_PRESS) {
				camera->transform.Position.y +=  Time::deltaTime;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_KP_4) == GLFW_PRESS) {
				light->Position.x -=  Time::deltaTime;
			}


			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_KP_6) == GLFW_PRESS) {
				light->Position.x +=  Time::deltaTime;
			}


			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_KP_8) == GLFW_PRESS) {
				light->Position.y +=  Time::deltaTime;
			}


			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_KP_2) == GLFW_PRESS) {
				light->Position.y -=  Time::deltaTime;
			}
#pragma endregion

			_renderer.Update();

			manager.UpdateWindow();
		}
		manager.DestroyWindow();
	}
}