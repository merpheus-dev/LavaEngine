#pragma once
#include "../../Renderer/RenderObject.h"
#include "../../Renderer/Mesh.h"
#include "GLMeshData.h"
#include "GLVAO.h"
#include <memory>
namespace Lava {
	namespace OpenGL {
		struct GLRenderObject :public RenderObject {
			GLRenderObject(Lava::Mesh mesh,Lava::Material material);
			void EnableAttributes();
			void DisableAttributes();
			bool HasTexture();
			bool HasNormalMap();

			std::shared_ptr<GLVertexBuffer> m_vbo;
			std::shared_ptr<GLVertexBuffer> m_normalBuffer;
			std::shared_ptr<GLIndexBuffer> m_ibo;
			std::shared_ptr<GLVertexBuffer> m_texCoord;
			std::shared_ptr<GLVertexBuffer> m_tangentBuffer;
			GLVAO* m_vao;
			const char* name;
		};
	}
}