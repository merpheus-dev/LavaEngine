#include "Demo.h"
#include "../src/Utils/AssetImporter.h"
#include "../src/Core/AssetDatabase.h"
#include "../src/Components/Camera.h"
#include "../src/Components/Light.h"
#include "../src/Core/Scene.h"
#include "../src/Utils/Mathematics.h"
#include "../src/Core/InputManager.h"
void Lava::Demo::DemoGameLayer::Start()
{
	scene = new Scene("Assets/first.xml");
	renderer = new OpenGL::GLMasterRenderer(scene);
	for (auto& sceneObject : scene->SceneObjects)
	{
		auto batched_entities = dynamic_cast<BatchedEntities*>(sceneObject);
		if (batched_entities)
		{

			entities.insert(entities.end(), batched_entities->batch->begin(), batched_entities->batch->end());
		}
	}

	debug_ui = new DebugUI();
	debug_ui->Setup();
	debug_ui->light_pos = &(scene->scene_data->lights->at(0)->Position);

	auto particle_texture = AssetDatabase::LoadTexture("Assets/smoke.png", 4);
	//audio_source = new AudioSource();
	//audio_source->isLooping = true;
	//audio_source->SetClip("Assets/mm.wav");
	//audio_source->Play();
	//
	water_transform = new Transform();
	water_transform->Position = glm::vec3(0.f, 1., 2.f);
	auto glRenderer = static_cast<Lava::OpenGL::GLMasterRenderer*>(renderer);
	glRenderer->setup_water_renderer(water_transform);
	gl_water_renderer = (OpenGL::GLWaterRenderer*)glRenderer->waterRenderer;
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
	//auto tex_ids = std::vector<int>{ refractionTexId ,reflectionTexId };
	//debug_ui->Start(tex_ids);

	particle_system = new ParticleSystem();
	particle_system->texturePtr = new ParticleTexture(particle_texture->texture_id, 8);
	particle_system->gravity_effect = 0;
	particle_system->life_length = 4;
	particle_system->emission_rate = 1;
	particle_system->speed = .5;
	particle_system->randomize_count = true;
	particle_system->scale = glm::vec3(.5f);
	particle_system->deviation = .2f;
	particle_system->shape = Lava::Shape::Sphere;
	particle_system->direction = glm::vec3(0, 1, 0);
	particle_renderer = static_cast<OpenGL::GLParticleRenderer*>(renderer->particleRenderer);
	particle_renderer->AttachParticleSystem(particle_system);
	particle_move_pos_temp = glm::vec3(0.);
	onStartExecuted = false;
}

void Lava::Demo::DemoGameLayer::Update()
{
	auto _renderer = static_cast<Lava::OpenGL::GLMasterRenderer*>(renderer);
	camera = scene->ActiveCamera;
	debug_ui->LoopBegin();
	Time::CalculateDeltaTime();

	for (auto& entity : entities) {
		_renderer->batchedRenderer->AddToBatch(entity);
	}

	Lava::Demo::CameraController::Update(camera);

	/*
	auto& audio_engine = Lava::AudioEngine::GetEngine();
	audio_engine.set3dSourcePosition(audio_source->handle, 0, 0, 0);
	audio_engine.set3dListenerPosition(camera->transform.Position.x, camera->transform.Position.y, camera->transform.Position.z);
	audio_engine.set3dListenerAt(camera->transform.Rotation.x, camera->transform.Rotation.y, camera->transform.Rotation.z);
	 */

	if (InputManager::GetKeyPress(GLFW_KEY_O))
	{
		particle_system->generate_particles(particle_move_pos_temp);
		if (particle_move_pos_temp.z >= 2) particle_move_pos_temp.z = 0;
	}
	particle_system->update(camera);
	/*
#pragma  region Reflection Render
	float camera_height_distance = 2 * (camera->transform.Position.y - water_transform->Position.y);
	gl_water_renderer->BindReflectionFbo();
	camera->transform.Position.y -= camera_height_distance;
	camera->transform.Rotation.z *= -1;
	_renderer->Update(glm::vec4(0, 1, 0, -(water_transform->Position.y)));
	for (auto& entity : entities) {
		_renderer->batchedRenderer->AddToBatch(entity);
	}
	camera->transform.Position.y += camera_height_distance;
	camera->transform.Rotation.z *= -1;
#pragma endregion

#pragma region Refraction Render
	gl_water_renderer->BindRefractionFbo();
	_renderer->Update(glm::vec4(0, -1, 0, water_transform->Position.y));
	gl_water_renderer->UnbindAll();
#pragma endregion
	
	for (auto& entity : entities) {
		_renderer->batchedRenderer->AddToBatch(entity);
	}
	*/
	gl_water_renderer->UnbindAll();
	glDisable(GL_CLIP_DISTANCE0);
	_renderer->Update(glm::vec4(0, 1, 0, 10000));
	//_renderer->waterRenderer->Update(scene);
	debug_ui->Render();
	debug_ui->LoopEnd();
}
