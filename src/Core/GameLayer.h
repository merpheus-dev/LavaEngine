#pragma once
#include "../Renderer/MasterRenderer.h"
namespace Lava
{
	class GameLayer
	{
	public:
		virtual void Start() = 0;
		virtual void Update() = 0;
	public:
		
		Scene* scene;
		Lava::MasterRenderer* renderer;
	};
}
