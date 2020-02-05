#pragma once
#include "Transform.h"
namespace Lava {
	class Camera {
	public:
		Transform transform;
		float fov=70.f;
	};
}