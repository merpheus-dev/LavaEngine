#include "DebugUI.h"
#include <iostream>

void DebugUI::Render()
{
	//if (tex_ids.size() != 0)
	//	ImGui::Image((void*)tex_ids[0], ImVec2(800,600));
}

void DebugUI::Start(std::vector<int> texture_ids)
{
	tex_ids = texture_ids;
}
