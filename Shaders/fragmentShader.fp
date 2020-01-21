#version 400 core

in vec2 pass_textureCoords;
uniform sampler2D textureSampler;
out vec4 output_color;

void main(void){
	output_color = texture(textureSampler,pass_textureCoords);
}