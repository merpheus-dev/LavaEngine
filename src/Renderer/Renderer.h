#pragma once
#include <memory>
#include "RenderObject.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/Entity.h"
#include <map>
namespace Lava {
	class Renderer {
	public:
		virtual void BindAttribute(int variableIndex, const char* variableName) = 0;
		virtual void Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
		virtual void SetLightInfo(Light& light) = 0;
		virtual void SetFogInfo() = 0;
		virtual void CompleteRender() = 0;
		virtual void PushInstanceData(Entity* entityPtr) = 0;
		virtual void BindObjects(Entity* entityPtr) = 0;
		virtual void UnBindObjects(Entity* entityPtr) = 0;
		virtual void Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities) = 0;
		virtual void Update(Camera camera,Light light) = 0;
	};
}