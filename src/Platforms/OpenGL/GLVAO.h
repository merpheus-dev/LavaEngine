#pragma once
#include "../../Renderer/VertexArrayObject.h"
#include "GLMeshData.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <vector>
namespace Lava {
	namespace OpenGL {
		class GLVAO : VertexArrayObject {
		public:
			GLVAO();
			virtual ~GLVAO();
			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual void AddVertexBufferObject(const std::shared_ptr<VertexBuffer>& vertexBuffer,int bufferIndex) override;
			virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		private:
			GLuint m_vaoId;
			std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer;
			std::shared_ptr<IndexBuffer> m_indexBuffer;
		};
	}
}