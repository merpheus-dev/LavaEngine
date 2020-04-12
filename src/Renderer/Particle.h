#pragma once
#include "../Components/Transform.h"
#include "../Core/Physics.h"
#include "../Core/LavaTime.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "ParticleTexture.h"
namespace Lava
{
	struct Particle
	{
		Transform* transform;
		ParticleTexture* texturePtr;
		glm::vec3 velocity;
		float gravity_effect;
		float life_length;
		float elapsed_time = 0.f;
		glm::vec2 current_sheet_offset;
		glm::vec2 next_sheet_offset;
		float sheet_blend;

		Particle(ParticleTexture* texture, const glm::vec3 position, const glm::vec3 rotation,const glm::vec3 scale,const glm::vec3 velocity,const float gravity_effect, const float life_time)
			:transform(new Transform(position,rotation,scale)), velocity(velocity),gravity_effect(gravity_effect),life_length(life_time), texturePtr(texture)
		{
			
		}

		bool update()
		{
			velocity.y += Physics::GRAVITY_MODIFIER * gravity_effect * Time::deltaTime;
			transform->Position+= velocity * Time::deltaTime;
			UpdateTextureOffsets();
			elapsed_time += Time::deltaTime;
			return  elapsed_time < life_length;
		}

		glm::mat4 GetFacingTransformationMatrix(glm::mat4 viewMatrix)
		{
			//TO-DO: Find a quicker way to get 3x3 parts, then you can transpose it and assign back
			auto matrix = glm::identity<glm::mat4>();
			matrix = glm::translate(matrix, transform->Position);
			matrix[0][0] = viewMatrix[0][0];
			matrix[0][1] = viewMatrix[1][0];
			matrix[0][2] = viewMatrix[2][0];
			matrix[1][0] = viewMatrix[0][1];
			matrix[1][1] = viewMatrix[1][1];
			matrix[1][2] = viewMatrix[2][1];
			matrix[2][0] = viewMatrix[0][2];
			matrix[2][1] = viewMatrix[1][2];
			matrix[2][2] = viewMatrix[2][2];
			matrix = glm::rotate(matrix, glm::radians(transform->Rotation.x), glm::vec3(1, 0, 0));
			matrix = glm::rotate(matrix, glm::radians(transform->Rotation.y), glm::vec3(0, 1, 0));
			matrix = glm::rotate(matrix, glm::radians(transform->Rotation.z), glm::vec3(0, 0, 1));
			matrix = glm::scale(matrix, transform->Scale);
			matrix = viewMatrix * matrix;
			return matrix;
		}

	private:
		void UpdateTextureOffsets()
		{
			auto life_percentage = elapsed_time / life_length;
			auto sheet_count = glm::pow(texturePtr->number_of_rows, 2);
			auto progression = life_percentage * sheet_count;
			auto current_sheet_index = static_cast<int>(glm::floor(progression));
			auto next_sheet_index = current_sheet_index + (current_sheet_index + 1 < sheet_count ? 1 : 0);
			sheet_blend = progression - current_sheet_index; //3.5-3 = 0.5
			current_sheet_offset= CalculateOffset(current_sheet_index);
			next_sheet_offset = CalculateOffset(next_sheet_index);
		}

		glm::vec2 CalculateOffset(int index)
		{
			auto col = index % texturePtr->number_of_rows;
			auto row = index / texturePtr->number_of_rows;

			return glm::vec2(static_cast<float>(col) / texturePtr->number_of_rows, static_cast<float>(row) / texturePtr->number_of_rows);
		}
	};
}
