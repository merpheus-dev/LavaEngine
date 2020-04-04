#pragma once
#include "../Components/Transform.h"
#include "../Core/Physics.h"
#include "../Core/LavaTime.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
namespace Lava
{
	struct Particle
	{
		Transform* transform;
		glm::vec3 velocity;
		float gravity_effect;
		float life_length;
		float elapsed_time = 0.f;

		Particle(const glm::vec3 position, const glm::vec3 rotation,const glm::vec3 scale,const glm::vec3 velocity,const float gravity_effect, const float life_time)
			:transform(new Transform(position,rotation,scale)), velocity(velocity),gravity_effect(gravity_effect),life_length(life_time)
		{
			
		}

		bool update()
		{
			velocity.y += Physics::GRAVITY_MODIFIER * gravity_effect * Time::deltaTime;
			transform->Position+= velocity * Time::deltaTime;
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
	};
}
