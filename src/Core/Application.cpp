#include "Application.h"
#include "WindowManager.h"
#include "../Platforms/OpenGL/GLRenderer.h"
#include "../Renderer/Mesh.h"
#include "../Platforms/OpenGL/GLShader.h"
#include "../Platforms/OpenGL/GLShaderBank.h"
#include "../Core/AssetDatabase.h"
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
		float texCoords[8] = {
			0,0,
			0,1,
			1,1,
			1,0
		};

		Lava::Mesh* mesh = new Mesh();
		mesh->m_positions = vertices;
		mesh->m_posCount = 12;
		mesh->m_indices = indices;
		mesh->m_indiceCount = 6;
		mesh->m_bufferLayoutElement = new VertexBufferElement[2];
		mesh->m_bufferLayoutElement[0].uniform_name = "position";
		mesh->m_bufferLayoutElement[0].uniform_count = 3;
		mesh->m_bufferLayoutElement[1].uniform_name = "texCoord";
		mesh->m_bufferLayoutElement[1].uniform_count = 2;
		mesh->m_bufferLayoutCount = 2;

		auto material = new Material();
		auto texture = AssetDatabase::LoadTexture("Assets/e.jpg");
		material->m_mainTexture = &texture;
		material->m_uvCoords = texCoords;
		material->m_uvCoordCount = 8;

		auto objekt = new OpenGL::GLRenderObject(*mesh, *material);
		objekt->name = "Anan";

		renderer.AddRenderObject(objekt);
		renderer.BindAttribute(0, "position");
		renderer.BindAttribute(1, "texCoord");

		while (!manager.IsWindowClosed()) {
			renderer.Update();
			manager.UpdateWindow();
		}
		manager.DestroyWindow();
	}
}