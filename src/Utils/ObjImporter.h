#pragma once
#include "../Renderer/MeshMaterialPack.h"
#include "TextUtils.h"
#include <vector>
#include "glm.hpp"
#include <sstream>
#include <iostream>
#include <string>
namespace Lava {
	namespace Importers {
		class ObjImporter {
		private:
			static std::vector<glm::vec3> vertices;
			static std::vector<glm::vec2> textures;
			static std::vector<glm::vec3> normals;
			static std::vector<float> texCoords;
			static std::vector<int> indices;
		public:

			static MeshMaterialPack* Load(const char* fileName)
			{
				MeshMaterialPack* pack = new MeshMaterialPack();
				std::string fileContent = TextUtils::ReadText(fileName);
				vertices.clear();
				textures.clear();
				normals.clear();
				indices.clear();
				pack->mesh = new Mesh();
				pack->material = new Material();
				bool texCoordAssigned = false;

				std::istringstream stream(fileContent);
				std::string line;
				bool initialTags = false;
				while (std::getline(stream, line)) {
					std::istringstream currentLine(line);
					if (!initialTags && line.substr(0, 2) != "v ")
						continue;
					else
						initialTags = true;

					std::string chunk;
					int dataType = -1;
					glm::vec3 vec3;
					glm::vec2 vec2;
					int i = 0;
					while (std::getline(currentLine, chunk, ' ')) {
						if (line.substr(0, 2) == "v " && chunk.substr(0, 1) != "v")
						{
							vec3[i] = std::stof(chunk);
							i++;
							dataType = 0;
						}
						else if (line.substr(0, 3) == "vt " && chunk.substr(0, 2) != "vt") {
							vec2[i] = std::stof(chunk);
							i++;
							dataType = 1;
						}
						else if (line.substr(0, 3) == "vn " && chunk.substr(0, 2) != "vn") {
							vec3[i] = std::stof(chunk);
							i++;
							dataType = 2;
						}
						else if (line.substr(0, 2) == "f ") {
							dataType = 3;
							break;
						}
					}
					switch (dataType) {
					case 0: //v
						vertices.push_back(vec3);
						break;
					case 1: //vt
						textures.push_back(vec2);
						break;
					case 2: //vn
						normals.push_back(vec3);
						break;
					}

					if (dataType == 3 && line.substr(0, 2) == "f ")
					{
						if (!texCoordAssigned) {
							texCoords = std::vector<float>(vertices.size()*2);
							texCoordAssigned = true;
						}

						int faceInfo[3][3];
						std::string faceChunk;
						int i = 0;
						while (std::getline(currentLine, chunk, ' ')) {
							std::istringstream face(chunk);
							int j = 0;
							while (std::getline(face, faceChunk, '/')) {
								faceInfo[i][j] = std::stoi(faceChunk);
								j++;
							}
							i++;
						}
						GenerateArrays(faceInfo, pack);
					}
				}
				//To-Do: Implement memcpy instead
				pack->mesh->m_posCount = vertices.size() * 3;
				pack->mesh->m_positions = new float[pack->mesh->m_posCount];
				int i = 0;
				for (auto& vertex : vertices) {
					pack->mesh->m_positions[i++] = vertex.x;
					pack->mesh->m_positions[i++] = vertex.y;
					pack->mesh->m_positions[i++] = vertex.z;
				}
				pack->mesh->m_indiceCount = indices.size();
				pack->mesh->m_indices = new int[pack->mesh->m_indiceCount];
				for (int j = 0; j < indices.size(); j++) {
					pack->mesh->m_indices[j] = indices[j];
				}


				pack->material->SetTexture(nullptr, texCoords);
				return pack;
			}

			static void GenerateArrays(int faceInfo[3][3], MeshMaterialPack* pack)
			{
				for (int i = 0; i < 3; i++) {
					int indice = faceInfo[i][0] - 1;
					indices.push_back(indice);
					int tex = faceInfo[i][1] - 1;
					texCoords[indice * 2] = textures[tex].x;
					texCoords[indice * 2 + 1] =1- textures[tex].y;
				}
			}

		};

	}
}