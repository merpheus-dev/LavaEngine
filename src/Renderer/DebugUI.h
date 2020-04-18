#pragma once
#include "../Core/WindowManager.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <vector>
#include <vec3.hpp>

class DebugUI
{
public:
	void Render();
	void Start(std::vector<int> texture_ids);
	void Setup()
	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(Lava::WindowManager::m_window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
		ImGui::StyleColorsDark();
		ImGuiIO io = ImGui::GetIO();
		m_font = io.Fonts->AddFontFromFileTTF("Assets/Roboto-Regular.ttf", 28.0);
	}
	void LoopBegin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void LoopEnd() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	~DebugUI() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
public:
	glm::vec3* light_pos;

protected:
	ImFont* m_font;
	std::vector<int> tex_ids;

};
