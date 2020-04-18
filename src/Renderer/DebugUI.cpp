#include "DebugUI.h"
#include <iostream>

void DebugUI::Render()
{
    ImGui::Begin("Scene Window");
    //get the mouse position
    ImVec2 pos = ImGui::GetCursorScreenPos();

    //pass the texture of the FBO
    //window.getRenderTexture() is the texture of the FBO
    //the next parameter is the upper left corner for the uvs to be applied at
    //the third parameter is the lower right corner
    //the last two parameters are the UVs
    //they have to be flipped (normally they would be (0,0);(1,1)
    int i = 0;
	for(auto& tex_id :tex_ids)
	{
        ImGui::GetWindowDrawList()->AddImage(
            (void*)tex_id,
            ImVec2(ImGui::GetCursorScreenPos().x+480*i, ImGui::GetCursorScreenPos().y),
            ImVec2(ImGui::GetCursorScreenPos().x + 480*(i+1),
                ImGui::GetCursorScreenPos().y + 320), ImVec2(0, 1), ImVec2(1, 0));
        i++;
	}
    auto a = new float*[3]{ &light_pos->x,&light_pos->y,&light_pos->z };
    ImGui::DragFloat3("Light Pos",*a);
    ImGui::End();
}

void DebugUI::Start(std::vector<int> texture_ids)
{
    tex_ids = texture_ids;
}
