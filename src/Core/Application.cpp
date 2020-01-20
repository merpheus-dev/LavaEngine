#include "Application.h"
#include "WindowManager.h"
#include "../Platforms/OpenGL/GLRenderer.h"
#include "../Renderer/Mesh.h"
#include "../Platforms/OpenGL/GLShader.h"
#include "../Platforms/OpenGL/GLShaderBank.h"
#include <iterator>
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

		int indices[6] = {
			0,1,3,
			3,1,2
		};

		Lava::Mesh* mesh = new Mesh();
		mesh->m_positions = vertices;
		mesh->m_posCount = 12;
		mesh->m_indices = indices;
		mesh->m_indiceCount = 6;
		mesh->m_bufferLayoutElement = new VertexBufferElement[2];
		mesh->m_bufferLayoutElement->uniform_name = "position";
		mesh->m_bufferLayoutElement->uniform_count = 3;
		mesh->m_bufferLayoutCount = 1;


		//shaderBank->LogBoundShaders();

		auto* objekt = new OpenGL::GLRenderObject(*mesh);
		objekt->name = "Anan";
		renderer.AddRenderObject(objekt);


		while (!manager.IsWindowClosed()) {
			renderer.Update();
			manager.UpdateWindow();
		}
		manager.DestroyWindow();
	}
}