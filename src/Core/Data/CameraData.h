#pragma once
#include <matrix.hpp>
struct CameraData {
	glm::mat4 View;
	glm::mat4 Projection;
	glm::mat4 LightSpaceMatrix;
	unsigned int ShadowMapTextureId;
};