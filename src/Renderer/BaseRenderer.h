#pragma once
#include <memory>
#include "RenderObject.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/Entity.h"
#include "../Core/Scene.h"
#include <map>
namespace Lava {
	class BaseRenderer {
	public:
		BaseRenderer(Scene* scene) : m_scene(scene){}
		virtual void Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
		virtual void CompleteRender() = 0;
		virtual void Update(Scene* scene) = 0;

	protected:
		Scene* m_scene;
	};
}