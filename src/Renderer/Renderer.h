#pragma once
#include <memory>
#include "RenderObject.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
namespace Lava {
	class Renderer {
	public:
		virtual void BindAttribute(int variableIndex, const char* variableName) = 0;
		//virtual ~Renderer() = default;
		virtual void Update(Camera camera,Light light) = 0;
		//virtual void AddRenderObject(std::shared_ptr<RenderObject>& renderObject) = 0;
	};
}