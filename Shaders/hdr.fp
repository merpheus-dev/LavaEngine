#version 400 core
out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D hdrTexture;
uniform float exposure;

void main()
{
	vec3 hdrColor = texture(hdrTexture,texCoords).rgb;
	FragColor = vec4(hdrColor,1.0);
}