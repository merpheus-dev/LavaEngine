#pragma once
#include "../../Renderer/MeshData.h";
#include <GL/glew.h>
#include <glfw3.h>
namespace Lava {
	namespace OpenGL {
		class GLVertexBuffer :public VertexBuffer {
		public:
			GLVertexBuffer(float* vertex_positions, unsigned int size);
			virtual ~GLVertexBuffer();
			virtual void Bind() const override;
			virtual void UnBind() const override;
			virtual VertexBufferElement* GetBufferElements() const override { return m_bufferElement; }
			virtual int GetBufferElementCount() const override { return *m_bufferElementCount; }
			virtual void SetBufferElements(VertexBufferElement* element,int* bufferElementCount);
		private:
			unsigned int m_bufferId;
			VertexBufferElement* m_bufferElement;
			int* m_bufferElementCount;
			int m_size;
		};

		class GLIndexBuffer :public IndexBuffer {
		public:
			GLIndexBuffer(int* indices,unsigned int& size);
			virtual ~GLIndexBuffer();
			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual int GetSize() const override;
		private:
			GLuint m_bufferId;
			unsigned int m_count;
		};
	}
}