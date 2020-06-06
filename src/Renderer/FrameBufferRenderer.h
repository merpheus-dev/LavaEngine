#pragma once
namespace Lava {
	class FrameBufferRenderer {
	public:
		void SetFrameBuffers(unsigned int& colorFbo);
		unsigned int colorBufferFbo;
	};
}