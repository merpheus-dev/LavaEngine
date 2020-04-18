#include "Scene.h"
#include "../Components/Light.h"
#include "../Utils/TextUtils.h"
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
	auto position = camera->FirstChildElement("Position")->GetText();
	auto rotation = camera->FirstChildElement("Rotation")->GetText();
	ActiveCamera = new Camera();
	ActiveCamera->transform.Position = parse_vector3(position);
	ActiveCamera->transform.Rotation = parse_vector3(rotation);
}

void Lava::Scene::LoadBatchedEntities()
{
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
