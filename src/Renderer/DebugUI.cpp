#include "DebugUI.h"
#include <iostream>
#include <gtc/type_ptr.hpp>
void DebugUI::Render()
{
	if (tex_ids.size() != 0)
		ImGui::Image((void*)tex_ids[0], ImVec2(480, 320));

	ImGui::SliderFloat3("Pos:", glm::value_ptr(*light_pos), -10, 10);
	//for (auto i = 0; i < 3; i++) {
	//	ImGui::SliderFloat("Pos", &(*light_pos)[i], -10, 10);
	//}
}

void DebugUI::Start(std::vector<int> texture_ids)
{
	tex_ids = texture_ids;
}
