#pragma once
#include <vector>
#include "MeshData.h"
namespace Lava {
	struct Mesh {
		float* m_positions;
		unsigned int m_posCount;
		float* m_normals;
		unsigned int m_normCount;
		float* m_tangents;
		unsigned int m_tangentCount;
		int* m_indices;
		unsigned int m_indiceCount;
		float* m_uvCoords;
		unsigned int m_uvCoordCount;

		VertexBufferElement* m_bufferLayoutElement;
		int m_bufferLayoutCount;
	};
}