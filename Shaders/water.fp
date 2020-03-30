#version 400 core
in vec4 ClipSpace;

out vec4 out_Color;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main(void) {
	vec2 ndc = (ClipSpace.xy/ClipSpace.w)/2.f+.5f;

	vec4 reflectionColor = texture(reflectionTexture,vec2(ndc.x,1-ndc.y));
	vec4 refractionColor = texture(refractionTexture,ndc);
	out_Color = mix(reflectionColor,refractionColor,.5f);
}