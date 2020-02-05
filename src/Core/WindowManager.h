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
		static int m_windowWidth;
		static int m_windowHeight;
		const char* m_titlePtr;

	public:
		static GLFWwindow* m_window;
		static float GetAspectRatio();
	};
}