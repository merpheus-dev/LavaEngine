#pragma once
#include <vector>
namespace Lava {
	struct VertexBufferElement {
		const char* uniform_name;
		int uniform_count;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual VertexBufferElement* GetBufferElements() const = 0;
		virtual int GetBufferElementCount() const = 0;
		virtual void SetBufferElements(VertexBufferElement* element,int* bufferElementCount) = 0;
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual int GetSize() const = 0;
	};
}