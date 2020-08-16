#version 400 core
layout(location = 0)out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D scene;
uniform sampler2D bloomTex;
uniform float exposure;

void main()
{
	vec3 hdrColor = texture(scene,texCoords).rgb;
	vec3 bloomColor = texture(bloomTex,texCoords).rgb;
	//Additive blend
	hdrColor+=bloomColor; 

	//reinhard tonemap
	vec3 toneMapped = vec3(1.) - exp(-hdrColor * exposure);

	toneMapped = pow(toneMapped,vec3(1./2.2));	//gamma correction curve applied
	FragColor = vec4(toneMapped,1.0);
}