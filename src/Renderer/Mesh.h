#pragma once
#include <vector>
#include "MeshData.h"
namespace Lava {
	struct Mesh {
		float* m_positions;
		int m_posCount;
		float* m_normals;
		int m_normCount;
		int* m_indices;
		unsigned int m_indiceCount;
		VertexBufferElement* m_bufferLayoutElement;
		int m_bufferLayoutCount;
		//std::vector<float> positions;
		//std::vector<int> indices;
		//std::vector<VertexBufferElement> bufferLayoutElement;
	};
}