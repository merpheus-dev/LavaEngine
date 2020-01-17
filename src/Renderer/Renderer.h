#pragma once
#include <memory>
#include "RenderObject.h"
namespace Lava {
	class Renderer {
	public:
		//virtual ~Renderer() = 0;
		virtual void Update() = 0;
		//virtual void AddRenderObject(std::shared_ptr<RenderObject>& renderObject) = 0;
	};
}