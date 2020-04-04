#include "Application.h"
#include "WindowManager.h"
#include "../Platforms/OpenGL/GLRenderer.h"
#include "../Platforms/OpenGL/GLWaterRenderer.h"
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
#include "../Platforms/OpenGL/GLFrameBuffers.h"
#include "../Renderer/DebugUI.h"
#include "../Components/ParticleSystem.h"
#include "../Platforms/OpenGL/GLParticleRenderer.h"
namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;

		DebugUI* debug_ui = new DebugUI();
		debug_ui->Setup();
		
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

		//auto water_obj = Lava::Importers::AssetImporter::Load("Assets/water.obj");
		auto pack = Lava::Importers::AssetImporter::Load("Assets/Zombie9.obj");
		auto texture = AssetDatabase::LoadTexture("Assets/Zombie9_CT.png",4);
		//auto normal_map = AssetDatabase::LoadTexture("Assets/barrelNormal.png", 4);

		std::vector<Entity*> entities;
		MeshRenderer* batchableRenderer = nullptr;
		for (int a = 0; a < 50; a++) {
			Entity* entity = new Entity(glm::vec3(0., -.5, 0), pack);
			entity->SetBufferLayout(bufferElements);
			entity->material->m_mainTexture = &texture;
			//entity->material->m_nrmTexture = &normal_map;
			if (!batchableRenderer)
				batchableRenderer = entity->GetMeshRenderer(Platform::OpenGL);
			else
				entity->meshRenderer = batchableRenderer;
			entities.push_back(entity);
		}

		//Entity* water = new Entity(glm::vec3(0.f), water_obj);
		//water->SetBufferLayout(bufferElements);
		//water->material->m_mainTexture = &texture;
		//water->material->m_nrmTexture = &normal_map;
		////water->meshRenderer = batchableRenderer;
		//entities.push_back(water);
		Transform* water_transform = new Transform();
		water_transform->Position = glm::vec3(0.f, 1., 2.f);
		_renderer.setup_water_renderer(water_transform);
		auto gl_water_renderer = (OpenGL::GLWaterRenderer*)_renderer.waterRenderer;
		//auto frameBuffer = OpenGL::GLFrameBuffers();
		//auto frame_buffer_id = frameBuffer.CreateFrameBuffer();
		//auto color_tex = frameBuffer.CreateColorTextureAttachment(480, 320);
		//frameBuffer.CreateDepthBufferAttachment(480, 320);
		//auto waterRenderer = new OpenGL::GLWaterRenderer(_renderer.GetScenePtr(),water_transform);
		gl_water_renderer->SetReflectionDimensions(480, 320);
		gl_water_renderer->SetRefractionDimensions(480, 320);
		gl_water_renderer->InitReflectionAndRefractionFrameBuffers();
		auto reflectionTexId = gl_water_renderer->BindReflectionFbo();
		auto refractionTexId = gl_water_renderer->BindRefractionFbo();
		auto tex_ids = std::vector<int>{ refractionTexId ,reflectionTexId };
		debug_ui->Start(tex_ids);

		auto particleSystem = new ParticleSystem();
		auto particleRenderer = static_cast<OpenGL::GLParticleRenderer*>(_renderer.particleRenderer);
		particleRenderer->AttachParticleSystem(particleSystem);
		
		bool onStartExecuted = false;

		while (!manager.IsWindowClosed()) {
			debug_ui->LoopBegin();
			
			Time::CalculateDeltaTime();
			if (!onStartExecuted) {
				for (auto& eachEntity : entities) {
					for (int i = 0; i < 3; i++) {
						
						float randPos = Lava::Mathematics::GetRandom() / 50.f;
						eachEntity->transform->Position[i] = randPos;
					}
					std::cout << "POS:" << eachEntity->transform->Position.x << "," << eachEntity->transform->Position.y
						<< "," << eachEntity->transform->Position.z << std::endl;
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

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_O) == GLFW_PRESS)
			{
				particleSystem->add_particle(new Particle(glm::vec3(0), glm::vec3(0), glm::vec3(1),
					glm::vec3(0, 0, 0), 0, 2));
			}
			
			particleSystem->update();
			
			float camera_height_distance = 2 * (camera->transform.Position.y - water_transform->Position.y);
			gl_water_renderer->BindReflectionFbo();
			camera->transform.Position.y -= camera_height_distance;
			camera->transform.Rotation.z *= -1;
			_renderer.Update(glm::vec4(0,1, 0,-(water_transform->Position.y)));
			for (auto& entity : entities) {
				_renderer.batchedRenderer->AddToBatch(entity);
			}
			camera->transform.Position.y += camera_height_distance;
			camera->transform.Rotation.z *= -1;
			
			gl_water_renderer->BindRefractionFbo();
			//waterRenderer->BindRefractionFbo();
			//frameBuffer.BindFrameBuffer(frame_buffer_id, 480, 320);
			_renderer.Update(glm::vec4(0,-1,0, water_transform->Position.y));
			gl_water_renderer->UnbindAll();
			
			//frameBuffer.UnbindFrameBuffer();
			for (auto& entity : entities) {
				_renderer.batchedRenderer->AddToBatch(entity);
			}
			glDisable(GL_CLIP_DISTANCE0);
			_renderer.Update(glm::vec4(0, 1, 0, 10000));
			_renderer.waterRenderer->Update(scene);
			debug_ui->Render();
			debug_ui->LoopEnd();
			manager.UpdateWindow();
		}
		manager.DestroyWindow();
	}
}