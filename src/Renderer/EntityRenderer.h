#pragma once
#include <memory>
#include "RenderObject.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/Entity.h"
#include "BaseRenderer.h"
#include <map>
namespace Lava {
	class EntityRenderer :public BaseRenderer{
	public:
		virtual void SetLightInfo(Light& light) = 0;
		virtual void SetFogInfo() = 0;
	};
}