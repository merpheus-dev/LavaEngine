#pragma once
#include "../../Renderer/BatchedRenderer.h"
#include "GLShader.h"
#include "GLRenderer.h"
#include "../../Core/WindowManager.h"
#include <glm.hpp>
namespace Lava {
	namespace OpenGL {
		class GLBatchedRenderer : public BatchedRenderer{
		public:
			GLBatchedRenderer(Scene* scene,std::vector<GLShader*> shader_list);
			virtual ~GLBatchedRenderer();
			virtual void Update(Scene* scene) override;
			virtual void AddToBatch(Entity* entity) override;
		private:
			glm::mat4 GetProjectionMatrix(Camera& camera) {
				return glm::perspective<float>(glm::radians(camera.fov), WindowManager::GetAspectRatio(), camera.near_plane,camera.far_plane );
			}

			glm::mat4 GetViewMatrix(Camera& camera) {
				return glm::lookAt<float>(camera.transform.Position,camera.transform.Position+ glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
			}
		};
	}
}