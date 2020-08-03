#version 400 core
layout(location = 0)out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D colorTexture;
uniform float exposure;

void main()
{
	vec3 hdrColor = texture(colorTexture,texCoords).rgb;

	//reinhard tonemap
	vec3 toneMapped = hdrColor/(hdrColor+vec3(1.0));

	float luminance = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));

	//TODO:Enable back after linear(sRGB) texture pipeline integration.
	toneMapped = pow(toneMapped,vec3(1./2.2));	//gamma correction curve applied
	FragColor = vec4(toneMapped,1.0);
}