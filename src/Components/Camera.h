#pragma once
#include "Transform.h"
namespace Lava {
	class Camera {
	public:
		Transform transform;
		float fov = 70.f;
		float near_plane = 0.001f;
		float far_plane = 1000.0f;
	};
}