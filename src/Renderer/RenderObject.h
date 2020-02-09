#pragma once
#include "Material.h"
#include "Mesh.h"
namespace Lava {
	struct RenderObject {
		Mesh m_mesh;
		Material m_material;
	};
}