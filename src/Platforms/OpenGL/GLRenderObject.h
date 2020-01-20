#pragma once
#include "../../Renderer/RenderObject.h"
#include "../../Renderer/Mesh.h"
#include "GLMeshData.h"
#include "GLVAO.h"
#include <memory>
namespace Lava {
	namespace OpenGL {
		struct GLRenderObject :public RenderObject {
			GLRenderObject(Lava::Mesh mesh);
			void EnableAttributes();
			void DisableAttributes();
			std::shared_ptr<GLVertexBuffer> m_vbo;
			std::shared_ptr<GLIndexBuffer> m_ibo;
			GLVAO* m_vao;
			const char* name;
		};
	}
}