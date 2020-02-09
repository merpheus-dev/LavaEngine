#include "Scene.h"

void Lava::Scene::Load(const char* fileDir)
{
	std::string sceneContent = TextUtils::ReadText(fileDir);
	LoadModelInfos(sceneContent);
}

void Lava::Scene::LoadModelInfos(std::string sceneContext)
{
	std::istringstream stream(sceneContext);
	std::string line;
	while (std::getline(stream, line)) {

		std::string delimiter = "|";
		size_t pos = 0;
		std::string token;
		std::string modelFile = "";
		std::string textureFile = "";
		glm::vec3 pos_vec = glm::vec3(0);
		int step = 0;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			if (step == 0)
				modelFile = token;
			else if (step == 1)
				textureFile = token;

			line.erase(0, pos + delimiter.length());
			step++;
			if (step == 2)
			{
				std::string delimiter2 = ",";
				size_t pos2 = 0;
				std::string token2;
				int vec_index = 0;
				while ((pos2 = line.find(delimiter2)) != std::string::npos) {
					token2 = line.substr(0, pos2);
					if (vec_index < 3) {
						pos_vec[vec_index] = std::stof(token2);
					}
					else {
						break;
					}
					line.erase(0, pos2 + delimiter2.length());
					vec_index++;
				}
			}
		}
		ModelObjectInfo modelObject;
		modelObject.modelPath = modelFile.c_str();
		modelObject.texturePath = textureFile.c_str();
		modelObject.Position = pos_vec;
		SceneObjects.push_back(modelObject);
	}
}
