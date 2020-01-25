#include "ObjImporter.h"
namespace Lava {
	namespace Importers {
		std::vector<glm::vec3> ObjImporter::vertices;
		std::vector<glm::vec2> ObjImporter::textures;
		std::vector<glm::vec3> ObjImporter::normals;
		std::vector<float> ObjImporter::texCoords;
		std::vector<int> ObjImporter::indices;
	}
}