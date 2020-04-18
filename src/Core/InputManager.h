#pragma once
#include "WindowManager.h"
#include "Data/Event.h"
#include "GL/glew.h"
#include <glfw3.h>

namespace Lava
{
	class InputManager
	{
	public:
		static bool GetKeyPress(int key_code);
	};
}
