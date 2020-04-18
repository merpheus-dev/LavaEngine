#pragma once
#include "../Renderer/Particle.h"
#include "../Utils/Sorting.h"
#include <vector>
#include <glm.hpp>
#include <gtc/random.hpp>
namespace Lava
{
	enum class Shape
	{
		Cone,
		Sphere
	};
	class ParticleSystem
	{
	public:
		void generate_particles(glm::vec3 center)
		{
			auto count = static_cast<int>(glm::floor(emission_rate * Time::deltaTime));
			auto rand = glm::linearRand(0, count);
			count = count + static_cast<int>(randomize_count ? rand : 0.f) + emission_rate;
			for (auto i = 0; i < count; i++)
			{
				emit_particle(center);
			}
		}

		void update(Camera* camera)
		{
			for (size_t i = 0; i < particles.size(); i++)
			{
				if (!particles[i]->update(camera))
				{
					particles.erase(particles.begin() + i);
				}
			}
			Lava::Sorting::sort_particles(particles);
		}
	private:
		void emit_particle(glm::vec3 center)
		{
			auto velocity = glm::vec3(0);
			if (shape == Shape::Sphere)
			{
				velocity = random_sphere_direction();
			}
			else
			{
				velocity = random_cone_direction(direction, deviation * glm::pi<float>());
			}
			velocity = glm::normalize(velocity) * randomize_value(speed, speed_random_range);
			auto particle_scale = glm::vec3(0);
			for (auto i = 0; i < 3; i++)
				particle_scale[i] = randomize_value(scale[i], scale_random_range);
			const auto life_time = randomize_value(life_length, life_time_random_range);
			
			particles.push_back(new Particle(texturePtr,center, random_rotation(), particle_scale,
				velocity, gravity_effect, life_time));
		}

		glm::vec3 random_cone_direction(glm::vec3 direction,float angle) const
		{
			const auto deviation_angle = glm::cos(angle);
			const auto theta = glm::linearRand(0., 1.) * 2.f * glm::pi<float>();
			const auto z = deviation_angle + (glm::linearRand(0., 1.) * (1 - deviation_angle));
			const auto hypotenuse = glm::sqrt(1 - z * z);
			const auto x = hypotenuse * glm::cos(theta);
			const auto y = hypotenuse * glm::sin(theta);
			auto cone_direction = glm::vec4(x, y, z, 1);
			if(cone_direction.x!=0 || cone_direction.y!=0 || (cone_direction.z!=1 && cone_direction.z!=-1))
			{
				auto rotate_axis = glm::cross(direction, glm::vec3(0, 0, 1)); //up vector
				rotate_axis = glm::normalize(rotate_axis);
				auto rotate_angle = glm::acos(glm::dot(direction, glm::vec3(0, 0, 1)));
				auto rotation_matrix = glm::identity<glm::mat4>();
				rotation_matrix = glm::rotate(rotation_matrix, -rotate_angle, rotate_axis);
				cone_direction = rotation_matrix * cone_direction;
			}else if(cone_direction.z == -1)
			{
				cone_direction.z = 1;
			}
			return cone_direction;
		}

		glm::vec3 random_sphere_direction() const
		{
			const auto theta = glm::linearRand(0.f, 1.f) * 2.f * glm::pi<float>();
			const auto z = (glm::linearRand(0., 1.) * 2) - 1;
			const auto hypotenuse = glm::sqrt(1 - z * z);
			const auto x = hypotenuse * glm::cos(theta);
			const auto y = hypotenuse * glm::sin(theta);
			return glm::vec3(x, y, z);
		}

		glm::vec3 random_rotation() const
		{
			if (!randomize_rotation) return glm::vec3(0);
			return glm::vec3(glm::linearRand(0., 1.) * 360., glm::linearRand(0., 1.) * 360., glm::linearRand(0., 1.) * 360.);
		}

		float randomize_value(const float base_value, const float range) const
		{
			return base_value + (glm::linearRand(0., 1.) - .5f) * 2. * range;
		}

	public:
		std::vector<Particle*> particles;

	public:
		ParticleTexture* texturePtr;
		Shape shape;
		float emission_rate;
		glm::vec3 direction;
		glm::vec3 scale;
		float speed;
		float gravity_effect;
		float life_length;
		float deviation; //deviation from original direction [0,1]
		bool randomize_count;
		bool randomize_rotation;

		float speed_random_range;
		float life_time_random_range;
		float scale_random_range;
	};
}