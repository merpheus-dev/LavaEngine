#include "Scene.h"
#include "../Components/Light.h"
#include "../Utils/TextUtils.h"
#include "../Renderer/VertexArrayObject.h"
#include "../Utils/AssetImporter.h"
#include "AssetDatabase.h"
#include "../Components/MeshRenderer.h"
//Lava::Scene::Scene(const char* scene_file):ActiveCamera(nullptr),scene_data(new DataContainers::SceneData())
//{
//	scene_data->fog_color = glm::vec3(0, 0, 0);
//	scene_data->lights = new std::array<Light*, 4>();
//	for (auto& light : *scene_data->lights)
//	{
//		light = new Light(glm::vec3(0, 0, 0));
//	}
//}
Lava::Scene::Scene(const char* file_name) : m_scene_file_name(file_name)
{
	LoadScene();
}

void Lava::Scene::LoadScene()
{
	scene_parser.LoadFile(m_scene_file_name);
	scene_data = new DataContainers::SceneData();
	LoadLights();
	LoadFogData();
	LoadCamera();
	LoadBatchedEntities();
	LoadSeparateEntities();
}

void Lava::Scene::LoadLights()
{
	scene_data->lights = new std::array<Light*, 4>();
	auto xml_node = scene_parser.FirstChildElement("LavaScene")->FirstChildElement("SceneData")->FirstChildElement("Lights");
	auto j = 0;
	for (auto child = xml_node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		if (j > 3) break;
		printf(child->Name());
		const auto position_text = child->FirstChildElement("Position")->GetText();
		const auto color_text = child->FirstChildElement("Color")->GetText();
		const auto intensity_text = child->FirstChildElement("Intensity")->GetText();
		scene_data->lights->at(j) = new DirectionalLight();
		scene_data->lights->at(j)->Position = parse_vector3(position_text);
		scene_data->lights->at(j)->Color = parse_vector3(color_text);
		scene_data->lights->at(j)->Intensity = std::stof(intensity_text);
		j++;
	}
	while (j <= 3)
	{
		scene_data->lights->at(j) = new Light();
		j++;
	}
}

void Lava::Scene::LoadFogData()
{
	auto fog_data = scene_parser.FirstChildElement("LavaScene")
		->FirstChildElement("SceneData")->FirstChildElement("Fog");
	const auto color = fog_data->FirstChildElement("Color")->GetText();
	const auto density = fog_data->FirstChildElement("Density")->GetText();
	scene_data->fog_color = parse_vector3(color);
	scene_data->fog_density = std::stof(density);
}

void Lava::Scene::LoadCamera()
{
	auto camera = scene_parser.FirstChildElement("LavaScene")->FirstChildElement("SceneData")->FirstChildElement("Camera");
	const auto position = camera->FirstChildElement("Position")->GetText();
	const auto rotation = camera->FirstChildElement("Rotation")->GetText();
	ActiveCamera = new Camera();
	ActiveCamera->transform.Position = parse_vector3(position);
	ActiveCamera->transform.Rotation = parse_vector3(rotation);
}

void Lava::Scene::LoadBatchedEntities()
{
	auto batched_entities			 = scene_parser.FirstChildElement("LavaScene")->FirstChildElement("BatchedEntities");
	const auto model_path			 = batched_entities->FirstChildElement("ModelPath")->GetText();
	const auto material_albedo		 = batched_entities->FirstChildElement("Material")->FirstChildElement("AlbedoPath")->GetText();
	const auto material_albedo_color = batched_entities->FirstChildElement("Material")->FirstChildElement("AlbedoColor")->GetText();
	const auto material_normal		 = batched_entities->FirstChildElement("Material")->FirstChildElement("NormalPath")->GetText();

	std::vector<VertexBufferElement> bufferElements(4);
	bufferElements[0].uniform_name = "position";
	bufferElements[0].uniform_count = 3;
	bufferElements[1].uniform_name = "texCoord";
	bufferElements[1].uniform_count = 2;
	bufferElements[2].uniform_name = "normal";
	bufferElements[2].uniform_count = 3;
	bufferElements[3].uniform_name = "tangent";
	bufferElements[3].uniform_count = 3;

	const auto pack = Importers::AssetImporter::Load(model_path);
	const auto albedo = AssetDatabase::LoadTexture(material_albedo, 4);
	Texture* normal = nullptr;
	if (material_normal != nullptr && !std::string(material_normal).empty())
		normal = AssetDatabase::LoadTexture(material_normal, 4);


	MeshRenderer* batchRenderer = nullptr;
	auto batch_container = new BatchedEntities();
	auto entity_list = batched_entities->FirstChildElement("Entity");
	for (auto child = entity_list->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		const auto position = child->FirstChildElement("Position")->GetText();
		const auto rotation = child->FirstChildElement("Rotation")->GetText();
		const auto scale = child->FirstChildElement("Scale")->GetText();
		auto entity = new Entity(parse_vector3(position), pack);
		entity->transform->Rotation = parse_vector3(rotation);
		entity->transform->Scale = parse_vector3(scale);
		entity->SetBufferLayout(bufferElements);
		entity->material->m_mainTexture = albedo;
		entity->material->albedoColor = parse_vector3(material_albedo_color);
		if (normal)
			entity->material->m_nrmTexture = normal;
		if (!batchRenderer)
			batchRenderer = entity->GetMeshRenderer(Platform::OpenGL);
		else
			entity->meshRenderer = batchRenderer;
		batch_container->batch->push_back(entity);
	}
	SceneObjects.push_back(batch_container);
	//auto water_obj = Lava::Importers::AssetImporter::Load("Assets/water.obj");
}

void Lava::Scene::LoadSeparateEntities()
{
	auto entities = scene_parser.FirstChildElement("LavaScene")->FirstChildElement("Entities");
	//auto entity_list = entities->FirstChildElement("Entity");

	for (auto child = entities->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		const auto model_path = child->FirstChildElement("ModelPath")->GetText();
		const auto material_albedo = child->FirstChildElement("Material")->FirstChildElement("AlbedoPath")->GetText();
		const auto material_albedo_color = child->FirstChildElement("Material")->FirstChildElement("AlbedoColor")->GetText();
		const auto material_normal = child->FirstChildElement("Material")->FirstChildElement("NormalPath")->GetText();
		const auto material_tiling = child->FirstChildElement("Material")->FirstChildElement("Tiling")->GetText();
		const auto material_cast_shadows = child->FirstChildElement("Material")->FirstChildElement("CastShadows")->GetText();
		const auto material_receive_shadows = child->FirstChildElement("Material")->FirstChildElement("ReceiveShadows")->GetText();
		const auto position = child->FirstChildElement("Transform")->FirstChildElement("Position")->GetText();
		const auto rotation = child->FirstChildElement("Transform")->FirstChildElement("Rotation")->GetText();
		const auto scale = child->FirstChildElement("Transform")->FirstChildElement("Scale")->GetText();

		const auto tiling = std::stoi(material_tiling);
		const auto pack = Importers::AssetImporter::Load(model_path);
		const auto albedo = AssetDatabase::LoadTexture(material_albedo, 4, tiling);
		Texture* normal = nullptr;
		if (material_normal != nullptr && !std::string(material_normal).empty())
			normal = AssetDatabase::LoadTexture(material_normal, 4, tiling);


		//std::vector<VertexBufferElement> bufferElements(4);
		//bufferElements[0].uniform_name = "position";
		//bufferElements[0].uniform_count = 3;
		//bufferElements[1].uniform_name = "texCoord";
		//bufferElements[1].uniform_count = 2;
		//bufferElements[2].uniform_name = "normal";
		//bufferElements[2].uniform_count = 3;
		//bufferElements[3].uniform_name = "tangent";
		//bufferElements[3].uniform_count = 3;

		auto bufferArray = new VertexBufferElement[4];
		bufferArray[0].uniform_name = "position";
		bufferArray[0].uniform_count = 3;
		bufferArray[1].uniform_name = "texCoord";
		bufferArray[1].uniform_count = 2;
		bufferArray[2].uniform_name = "normal";
		bufferArray[2].uniform_count = 3;
		bufferArray[3].uniform_name = "tangent";
		bufferArray[3].uniform_count = 3;

		auto entity = new Entity(parse_vector3(position), pack);
		entity->transform->Rotation = parse_vector3(rotation);
		entity->transform->Scale = parse_vector3(scale);
		entity->mesh->m_bufferLayoutElement = bufferArray;
		entity->mesh->m_bufferLayoutCount = 4;
		//entity->SetBufferLayout(bufferElements);

		entity->material->castShadows = std::stoi(material_cast_shadows);
		entity->material->receiveShadows = std::stoi(material_receive_shadows);
		entity->material->m_mainTexture = albedo;
		entity->material->albedoColor = parse_vector3(material_albedo_color);
		if (normal)
			entity->material->m_nrmTexture = normal;

		SceneObjects.push_back(entity);
	}
}

glm::vec3 Lava::Scene::parse_vector3(const char* text) const
{
	std::stringstream string_stream(text);
	std::string s;
	glm::vec3 position{};
	auto i = 0;
	while (std::getline(string_stream, s, ','))
	{
		position[i] = std::stof(s);
		i++;
		if (i >= 3) break;
	}
	return position;
}
