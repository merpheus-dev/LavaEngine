#pragma once
#include "Platform.h"
#include "../Renderer/RenderObject.h"
#include "OpenGL/GLRenderObject.h"
namespace Lava {
	class PlatformInstanceGenerator {
	public:
		static RenderObject* GenerateRenderObject(Mesh* mesh, Material* material, Platform platform) {
			switch (platform)
			{
			case Platform::OpenGL:
				return new OpenGL::GLRenderObject(*mesh, *material);
				break;
			default:
				return nullptr;
				break;
			}
		}
	};
}