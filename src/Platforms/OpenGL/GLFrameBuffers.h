#pragma once
#include <gl/glew.h>
#include <glfw3.h>
namespace Lava
{
	namespace OpenGL
	{
		class GLFrameBuffers
		{
		public:
			void BindFrameBuffer(int frameBuffer,int width,int height);
			void UnbindFrameBuffer();
			const int CreateFrameBuffer();
			const int CreateDepthBufferAttachment(const int& width, const int& height);
			const int CreateColorTextureAttachment(const int& width, const int& height);
			const int CreateDepthTextureAttachment(const int& width, const int& height);
		};
	}
}