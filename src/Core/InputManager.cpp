#include "InputManager.h"
bool Lava::InputManager::GetKeyPress(int key_code)
{
	return glfwGetKey(WindowManager::m_window, key_code) == GLFW_PRESS;
}
