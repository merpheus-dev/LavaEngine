#pragma once
namespace Lava {
	class QuadRenderer {
	public:
		virtual void Setup() = 0;
		virtual void Render(unsigned int& targetTextureId) = 0;
		virtual ~QuadRenderer() = default;
		
	protected:
		float vertices[20] = {
			-1, 1, -1, -1, 1, 1, 1, -1
		};

		unsigned int k_vao;
		unsigned int k_vbo;
	};
}