#version 400 core

in vec3 texCoords;
out vec4 out_Color;

uniform samplerCube cubeMap;

void main(void){
	out_Color = texture(cubeMap,texCoords);
}