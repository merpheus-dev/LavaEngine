#pragma once
#include "MeshData.h"
#include <memory>
namespace Lava{
	class VertexArrayObject {
	public:
		virtual ~VertexArrayObject() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBufferObject(const std::shared_ptr<VertexBuffer>& vertexBuffer,int bufferIndex) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
	};
}