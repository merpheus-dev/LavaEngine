#include "Application.h"
#include "WindowManager.h"
#include "../Platforms/OpenGL/GLRenderer.h"
#include "../Platforms/OpenGL/GLRenderObject.h"
#include "../Renderer/Mesh.h"
#include "../Platforms/OpenGL/GLShader.h"
#include "../Platforms/OpenGL/GLShaderBank.h"
#include "../Core/AssetDatabase.h"
#include "../Components/Entity.h"
#include "../Components/Camera.h"
#include <iterator>
#include <vector>
#include <iostream>
namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;

		OpenGL::GLRenderer renderer = OpenGL::GLRenderer(std::vector<Lava::OpenGL::GLShader*>());
		float vertices[12] = {
			//bottom right triangle of quad
			   //-1.0f, -1.0f, 0.0f,
			   //1.0f, -1.0f, 0.0f,
			   //1.0f,  1.0f, 0.0f,
			//top left triangle of quad
			   -.5f,  .5f, 0.0f,
			   -.5f,  -.5f, 0.0f,
			   .5f,  -.5f, 0.0f,
			  .5f,  .5f, 0.0f
		};

		std::vector<float> vertex_list(12);
		memcpy(&vertex_list[0], vertices, 12 * sizeof(float));

		int indices[6] = {
			0,1,3,
			3,1,2
		};
		std::vector<int> indice_list(12);
		memcpy(&indice_list[0], indices, 6 * sizeof(int));

		float texCoords[8] = {
			0,0,
			0,1,
			1,1,
			1,0
		};
		std::vector<float> texCoord_list(12);
		memcpy(&texCoord_list[0], texCoords, 8 * sizeof(float));

		std::vector<VertexBufferElement> bufferElements(2);
		bufferElements[0].uniform_name = "position";
		bufferElements[0].uniform_count = 3;
		bufferElements[1].uniform_name = "texCoord";
		bufferElements[1].uniform_count = 2;

		Entity* entity = new Entity(glm::vec3(0.,0.,0));
		entity->SetMeshData(vertex_list, indice_list, bufferElements);

		auto texture = AssetDatabase::LoadTexture("Assets/e.jpg");
		entity->material->SetTexture(&texture, texCoord_list);

		auto objekt = entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject();
		renderer.AddRenderObject(entity);

		renderer.BindAttribute(0, "position");
		renderer.BindAttribute(1, "texCoord");

		Camera camera;

		while (!manager.IsWindowClosed()) {
			
			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
			{
				camera.transform.Position.z -= 0.001f;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
			{
				camera.transform.Position.z += 0.001f;
			}
			
			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
				camera.transform.Position.x -= 0.001f;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
				camera.transform.Position.x += 0.001f;
			}

			renderer.Update(camera);
			manager.UpdateWindow();
		}
		manager.DestroyWindow();
	}
}