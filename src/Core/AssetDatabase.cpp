#include "AssetDatabase.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Lava::Texture* Lava::AssetDatabase::LoadTexture(const char* file_name, int component_count) {
	Texture* texture = new Texture();
	texture->data = stbi_load(file_name, &texture->width, &texture->height,
		&texture->normal_channel_count, component_count);

	if (texture->data) {
		glGenTextures(1, &texture->texture_id);
		glBindTexture(GL_TEXTURE_2D, texture->texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		GLint format = component_count == 0 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0,
			format, GL_UNSIGNED_BYTE, texture->data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		Debug::Log("Failed to load texture");
	}
	stbi_image_free(texture->data);
	texture->valid = true;
	return texture;
}

int Lava::AssetDatabase::LoadCubeMap(std::vector<const char*> cubeMapFiles) {
	TextureCubeMap cubeMap;
	glGenTextures(1, &cubeMap.texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.texture_id);
	int i = 0;
	for (auto& cubeMapDir : cubeMapFiles)
	{
		Texture texture;
		texture.data = stbi_load(cubeMapDir, &texture.width, &texture.height,
			&texture.normal_channel_count, 4);
		if (texture.data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, texture.data);
			i++;
		}
		else {
			Debug::Log("Failed to load cubemap");
		}
		stbi_image_free(texture.data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return cubeMap.texture_id;
}