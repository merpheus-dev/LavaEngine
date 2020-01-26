#include "AssetImporter.h"
namespace Lava {
	namespace Importers {
		MeshMaterialPack* AssetImporter::Load(const char* filePath)
		{
			const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!scene)
			{
				std::cout << "Could not load file " << filePath << std::endl;
				return nullptr;
			}

			const aiMesh* model = scene->mMeshes[0];

			MeshMaterialPack* pack = new MeshMaterialPack();
			pack->mesh = new Mesh();
			pack->material = new Material();

			pack->mesh->m_posCount = model->mNumVertices*3;
			pack->mesh->m_positions = new float[model->mNumVertices * 3];
			pack->mesh->m_normCount = model->mNumVertices * 3;
			pack->mesh->m_normals = new float[model->mNumVertices * 3];

			pack->material->m_uvCoordCount = model->mNumVertices * 2;
			pack->material->m_uvCoords = new float[model->mNumVertices * 2];

			for (int i = 0; i < model->mNumVertices; i++) {
				pack->mesh->m_positions[i * 3] = model->mVertices[i].x;
				pack->mesh->m_positions[i * 3+1] = model->mVertices[i].y;
				pack->mesh->m_positions[i * 3+2] = model->mVertices[i].z;

				if (model->HasNormals()) {
					pack->mesh->m_normals[i * 3] = model->mNormals[i].x;
					pack->mesh->m_normals[i * 3+1] = model->mNormals[i].y;
					pack->mesh->m_normals[i * 3+2] = model->mNormals[i].z;
				}

				if (model->HasTextureCoords(0)) {
					pack->material->m_uvCoords[i * 2] = model->mTextureCoords[0][i].x;
					pack->material->m_uvCoords[i * 2 + 1] =1- model->mTextureCoords[0][i].y;
				}
			}

			pack->mesh->m_indiceCount = model->mNumFaces * 3;
			pack->mesh->m_indices = new int[model->mNumFaces * 3];

			for (int i = 0; i < model->mNumFaces; i++) {
				pack->mesh->m_indices[i * 3] = model->mFaces[i].mIndices[0];
				pack->mesh->m_indices[i * 3+1] = model->mFaces[i].mIndices[1];
				pack->mesh->m_indices[i * 3+2] = model->mFaces[i].mIndices[2];
			}

			return pack;
		}
	}
}
