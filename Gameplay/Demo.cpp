#include "Demo.h"
#include "../src/Utils/AssetImporter.h"
#include "../src/Core/AssetDatabase.h"
#include "../src/Components/Camera.h"
#include "../src/Components/Light.h"
#include "../src/Core/Scene.h"
#include "../src/Utils/Mathematics.h"
#include "../src/Core/InputManager.h"
#include "soloud_wav.h"

void Lava::Demo::DemoGameLayer::Start()
{
	camera = new Camera();
	light = new DirectionalLight(glm::vec3(.4, .4, .4));
	scene = new Scene();
	scene->scene_data->fog_color = glm::vec3(.3, .3, .3);
	scene->scene_data->fog_density = .5f;
	scene->scene_data->lights->at(0) = light;
	scene->ActiveCamera = camera;
	renderer = new OpenGL::GLMasterRenderer(scene);
	
	debug_ui = new DebugUI();
	debug_ui->Setup();


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
	auto pack = Importers::AssetImporter::Load("Assets/Zombie9.obj");
	auto texture = AssetDatabase::LoadTexture("Assets/Zombie9_CT.png", 4);
	auto particle_texture = AssetDatabase::LoadTexture("Assets/smoke.png", 4);
	//auto normal_map = AssetDatabase::LoadTexture("Assets/barrelNormal.png", 4);

	MeshRenderer* batchableRenderer = nullptr;
	entities = new std::vector<Entity*>();
	for (int a = 0; a < 50; a++) {
		Entity* entity = new Entity(glm::vec3(0., -.5, 0), pack);
		entity->SetBufferLayout(bufferElements);
		entity->material->m_mainTexture = &texture;
		//entity->material->m_nrmTexture = &normal_map;
		if (!batchableRenderer)
			batchableRenderer = entity->GetMeshRenderer(Platform::OpenGL);
		else
			entity->meshRenderer = batchableRenderer;
		entities->push_back(entity);
	}

	audio_source = new AudioSource();
	audio_source->isLooping = true;
	audio_source->SetClip("Assets/mm.wav");
	audio_source->Play();
	
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
	auto tex_ids = std::vector<int>{ refractionTexId ,reflectionTexId };
	debug_ui->Start(tex_ids);

	particle_system = new ParticleSystem();
	particle_system->texturePtr = new ParticleTexture(particle_texture.texture_id, 8);
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
	debug_ui->LoopBegin();
	Time::CalculateDeltaTime();
	if (!onStartExecuted) {
		for (auto& eachEntity : *entities) {
			for (int i = 0; i < 3; i++) {

				float randPos = Lava::Mathematics::GetRandom() / 50.f;
				eachEntity->transform->Position[i] = randPos;
			}
			std::cout << "POS:" << eachEntity->transform->Position.x << "," << eachEntity->transform->Position.y
				<< "," << eachEntity->transform->Position.z << std::endl;
		}
		onStartExecuted = true;
	}
	for (auto& entity : *entities) {
		_renderer->batchedRenderer->AddToBatch(entity);
	}
	
	if(InputManager::GetKeyPress(GLFW_KEY_J))
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
	/*
	auto& audio_engine = Lava::AudioEngine::GetEngine();
	audio_engine.set3dSourcePosition(audio_source->handle, 0, 0, 0);
	audio_engine.set3dListenerPosition(camera->transform.Position.x, camera->transform.Position.y, camera->transform.Position.z);
	audio_engine.set3dListenerAt(camera->transform.Rotation.x, camera->transform.Rotation.y, camera->transform.Rotation.z);
	 */

	if(InputManager::GetKeyPress(GLFW_KEY_O))
	{
		particle_system->generate_particles(particle_move_pos_temp);
		if (particle_move_pos_temp.z >= 2) particle_move_pos_temp.z = 0;
	}
	particle_system->update(camera);

	float camera_height_distance = 2 * (camera->transform.Position.y - water_transform->Position.y);
	gl_water_renderer->BindReflectionFbo();
	camera->transform.Position.y -= camera_height_distance;
	camera->transform.Rotation.z *= -1;
	_renderer->Update(glm::vec4(0, 1, 0, -(water_transform->Position.y)));
	for (auto& entity : *entities) {
		_renderer->batchedRenderer->AddToBatch(entity);
	}
	camera->transform.Position.y += camera_height_distance;
	camera->transform.Rotation.z *= -1;

	gl_water_renderer->BindRefractionFbo();
	_renderer->Update(glm::vec4(0, -1, 0, water_transform->Position.y));
	gl_water_renderer->UnbindAll();
	for (auto& entity : *entities) {
		_renderer->batchedRenderer->AddToBatch(entity);
	}
	glDisable(GL_CLIP_DISTANCE0);
	_renderer->Update(glm::vec4(0, 1, 0, 10000));
	_renderer->waterRenderer->Update(scene);
	debug_ui->Render();
	debug_ui->LoopEnd();
}
