#version 400 core
out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D colorTexture;
uniform float exposure;

void main()
{
	vec3 hdrColor = texture(colorTexture,texCoords).rgb;

	//reinhard tonemap
	vec3 toneMapped = hdrColor/(hdrColor+vec3(1.0));


	//TODO:Enable back after linear(sRGB) texture pipeline integration.
	//toneMapped = pow(toneMapped,vec3(1./2.2));//gamma correction curve applied

	FragColor = vec4(toneMapped,1.0).rrra;
}