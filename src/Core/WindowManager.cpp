#include "WindowManager.h"
namespace Lava 
{
	WindowManager::WindowManager()
	{
		SetWindowTitle("Lava");
	}
	int WindowManager::GenerateWindow()
	{
		if (!glfwInit())
			return -1;

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_titlePtr, nullptr, nullptr);
		if (!m_window)
		{
			DestroyWindow();
			return -1;
		}

		glfwMakeContextCurrent(m_window);

		if (glewInit() != GLEW_OK)
			Debug::LogError("Window couldn't created.");

		Debug::LogInfo((char*)glGetString(GL_VERSION));
		return 1;
	}

	GLFWwindow* WindowManager::GetWindow()
	{
		return m_window;
	}

	void WindowManager::UpdateWindow()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void WindowManager::DestroyWindow()
	{
		glfwTerminate();
	}

	bool WindowManager::IsWindowClosed()
	{
		return glfwWindowShouldClose(m_window);
	}

	void WindowManager::SetWindowTitle(const char* title)
	{
		m_titlePtr = title;
	}
	void WindowManager::SetWindowResolution(int& width, int& height)
	{
		m_windowWidth = width;
		m_windowHeight = height;
	}

	float WindowManager::GetAspectRatio()
	{
		return WindowManager::m_windowWidth / (m_windowHeight*1.f);
	}

	GLFWwindow* WindowManager::m_window;
	int WindowManager::m_windowWidth = 1600;
	int WindowManager::m_windowHeight = 900;
}