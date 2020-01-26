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
#include "../Utils/ObjImporter.h"
#include "../Utils/AssetImporter.h"
namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;

		OpenGL::GLRenderer renderer = OpenGL::GLRenderer(std::vector<Lava::OpenGL::GLShader*>());
		/*float vertices[72] = {
				-0.5f,0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,0.5f,-0.5f,

				-0.5f,0.5f,0.5f,
				-0.5f,-0.5f,0.5f,
				0.5f,-0.5f,0.5f,
				0.5f,0.5f,0.5f,

				0.5f,0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,0.5f,
				0.5f,0.5f,0.5f,

				-0.5f,0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				-0.5f,-0.5f,0.5f,
				-0.5f,0.5f,0.5f,

				-0.5f,0.5f,0.5f,
				-0.5f,0.5f,-0.5f,
				0.5f,0.5f,-0.5f,
				0.5f,0.5f,0.5f,

				-0.5f,-0.5f,0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,0.5f
		};

		std::vector<float> vertex_list(72);
		memcpy(&vertex_list[0], vertices, 72 * sizeof(float));

		int indices[36] = {
				0,1,3,
				3,1,2,
				4,5,7,
				7,5,6,
				8,9,11,
				11,9,10,
				12,13,15,
				15,13,14,
				16,17,19,
				19,17,18,
				20,21,23,
				23,21,22
		};
		std::vector<int> indice_list(36);
		memcpy(&indice_list[0], indices, 36 * sizeof(int));

		float texCoords[48] = {
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0
		};
		std::vector<float> texCoord_list(48);
		memcpy(&texCoord_list[0], texCoords, 48 * sizeof(float));*/

		std::vector<VertexBufferElement> bufferElements(3);
		bufferElements[0].uniform_name = "position";
		bufferElements[0].uniform_count = 3;
		bufferElements[1].uniform_name = "texCoord";
		bufferElements[1].uniform_count = 2;
		bufferElements[2].uniform_name = "normal";
		bufferElements[2].uniform_count = 3;

		auto pack = Lava::Importers::AssetImporter::Load("Assets/Zombie9.obj");

		//auto pack = Lava::Importers::ObjImporter::Load("Assets/cube.obj");
		Entity* entity = new Entity(glm::vec3(0., -.5, 0), pack);
		entity->SetBufferLayout(bufferElements);
		//entity->SetMeshData(vertex_list, indice_list, bufferElements);

		auto texture = AssetDatabase::LoadTexture("Assets/Zombie9_CT.jpg");
		entity->material->AssignTexture(&texture);
		//entity->material->SetTexture(&texture, texCoord_list);

		auto objekt = entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject();
		renderer.AddRenderObject(entity);

		renderer.BindAttribute(0, "position");
		renderer.BindAttribute(1, "texCoord");
		renderer.BindAttribute(2, "normal");

		Camera camera;

		Light light = Light();

		while (!manager.IsWindowClosed()) {
			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
			{
				entity->transform->Rotation.y += .05f;
			}


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

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
				camera.transform.Position.y -= 0.001f;
			}

			if (glfwGetKey(manager.GetWindow(), GLFW_KEY_E) == GLFW_PRESS) {
				camera.transform.Position.y += 0.001f;
			}

			renderer.Update(camera,light);

			manager.UpdateWindow();
		}
		manager.DestroyWindow();
	}
}