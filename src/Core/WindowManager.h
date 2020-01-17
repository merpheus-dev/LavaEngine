#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "../Utils/Debug.h"
namespace Lava {
	class WindowManager {
	public:
		WindowManager();
		int GenerateWindow();
		GLFWwindow* GetWindow();
		void UpdateWindow();
		void DestroyWindow();
		bool IsWindowClosed();
		void SetWindowTitle(const char* title);
		void SetWindowResolution(int& width, int& height);

	private:
		GLFWwindow* m_window;
		int m_windowWidth=512;
		int m_windowHeight=512;
		const char* m_titlePtr;
	};
}