#pragma once
namespace Lava {
	class PostProcessingEffect {
	public:
		PostProcessingEffect():renderTargetID(0),colorTargetID(0),depthTargetID(0){}
		virtual void Init() = 0;
		virtual void Render(unsigned int baseColorTargetId,bool last) = 0; //pure virt func
		unsigned int colorTargetID;
	protected:
		unsigned int renderTargetID;
		unsigned int depthTargetID;
	};
}