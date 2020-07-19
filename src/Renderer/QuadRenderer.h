#pragma once
#include "PostProcessingEffect.h"
#include <vector>
namespace Lava {
	class QuadRenderer {
	public:
		virtual void Setup() = 0;
		virtual void Render(unsigned int& targetTextureId) = 0;
		virtual ~QuadRenderer() = default;
		std::vector<PostProcessingEffect*> postProcessingEffects;
	protected:
		float vertices[20] = {
			-1, 1, -1, -1, 1, 1, 1, -1
		};

		unsigned int k_vao;
		unsigned int k_vbo;
	};
}