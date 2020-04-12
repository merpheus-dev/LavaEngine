#pragma once
namespace Lava
{
	struct ParticleTexture
	{
		ParticleTexture(const unsigned int texture_id, const int row_count) : id(texture_id), number_of_rows(row_count)
		{
			
		}
		
		unsigned int id;
		int number_of_rows;
	};
}