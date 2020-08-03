#include "DebugUI.h"
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <ext.hpp>
#include <gtx/string_cast.hpp>
void DebugUI::Render()
{
	if (tex_ids.size() != 0)
		ImGui::Image((void*)tex_ids[0], ImVec2(480, 320));

	ImGui::SliderFloat3("Rot:", glm::value_ptr(*light_pos), -15, 15);
	//for (auto i = 0; i < 3; i++) {
	//	ImGui::SliderFloat("Pos", &(*light_pos)[i], -10, 10);
	//}
	std::string label("Position:");
	const glm::vec3 posLabel = *camera_pos;
	const glm::vec3 rotLabel = *camera_rot;
	label.append(glm::to_string(posLabel));
	label.append("\nRotation:");
	label.append(glm::to_string(rotLabel));
	ImGui::Text(label.c_str());
}

void DebugUI::Start(std::vector<int> texture_ids)
{
	tex_ids = texture_ids;
}
