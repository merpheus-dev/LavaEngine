#include "Application.h"
#include "WindowManager.h"
#include "../Platforms/OpenGL/GLRenderer.h"
#include "../Renderer/Mesh.h"
#include <iterator>
namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;

		OpenGL::GLRenderer renderer;
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
		//mesh.positions.insert(mesh.positions.end(), std::begin(vertices), std::end(vertices));
		//mesh.indices.insert(mesh.indices.end(),std::begin(indices),std::end(indices));
		//mesh.indices.insert(mesh.indices.end(), indices, indices + sizeof(float) * 6);
		mesh->m_bufferLayoutElement = new VertexBufferElement();
		mesh->m_bufferLayoutElement->uniform_name = "position";
		mesh->m_bufferLayoutElement->uniform_count = 3;
		mesh->m_bufferLayoutCount = 1;
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