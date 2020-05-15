#pragma once
#include <vector>
#include <glm.hpp>
#include "../Components/Entity.h"
namespace Lava {
	struct CameraData {
		glm::vec3 View;
		glm::vec3 Projection;
	};

	class NonbatchedRenderer {
	public:
		virtual ~NonbatchedRenderer() = 0;
		virtual void Render(CameraData& data) = 0;
		std::vector<Entity*> entity_list;

	private:
		virtual void LoadShaders() = 0;

	};
}