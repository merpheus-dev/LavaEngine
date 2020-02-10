#pragma once
#include <memory>
#include "RenderObject.h"
#include "../Components/Camera.h"
#include "../Core/Scene.h"
#include "../Components/Entity.h"
#include "BaseRenderer.h"
#include <map>
namespace Lava {
	class EntityRenderer :public BaseRenderer{
	public:
		virtual void SetLightInfo(Scene* scene) = 0;
		virtual void SetFogInfo() = 0;
	};
}