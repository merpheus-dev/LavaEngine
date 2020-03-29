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
		EntityRenderer(Scene* scene) : BaseRenderer(scene){}
		virtual void BindAttribute(int variableIndex, const char* variableName) = 0;
		virtual void SetLightInfo(Scene* scene) = 0;
		virtual void SetFogInfo() = 0;
		virtual void PushInstanceData(Entity* entityPtr) = 0;
		virtual void BindObjects(Entity* entityPtr) = 0;
		virtual void UnBindObjects(Entity* entityPtr) = 0;
		virtual void Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities, glm::vec4 clipPlane) = 0;
	};
}