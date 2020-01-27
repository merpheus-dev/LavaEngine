#pragma once
#include "../../Renderer/BatchedRenderer.h"
#include "GLShader.h"
#include "GLRenderer.h"
#include <glm.hpp>
namespace Lava {
	namespace OpenGL {
		class GLBatchedRenderer : public BatchedRenderer{
		public:
			GLBatchedRenderer(std::vector<GLShader*> shader_list);
			virtual ~GLBatchedRenderer();
			virtual void Update(Camera camera, Light light) override;
			virtual void AddToBatch(Entity* entity) override;
		private:
			glm::mat4 GetProjectionMatrix() {
				return glm::perspective<float>(glm::radians(70.0), 1.0, .001, 1000.);
			}

			glm::mat4 GetViewMatrix(Camera& camera) {
				return glm::lookAt<float>(camera.transform.Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			}
		};
	}
}