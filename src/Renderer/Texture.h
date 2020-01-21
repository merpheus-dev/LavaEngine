#pragma once
namespace Lava
{
	struct Texture {
		int width;
		int height;
		int normal_channel_count;
		unsigned int texture_id;
		unsigned char* data;
		bool valid = false;
	};
}