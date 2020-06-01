#version 400 core

in vec3 lightVector[4];
in vec2 pass_textureCoords;
in vec3 camVector;
in float fog;
in vec4 shadowCoords;

uniform sampler2D textureSampler;
uniform sampler2D normalMapSampler;
uniform sampler2D shadowMapSampler;
out vec4 output_color;

uniform vec3 LightColor[4];
uniform vec3 LightAttenuation[4];
uniform float LightIntensity[4];

uniform float Shininess;
uniform float GlossDamping;
uniform vec3 FogColor;
uniform float AmbientLightIntensity;
uniform int ShadowsOn;

void main(void){
	float shadow = 0.f;

	vec4 normalMapValue = 2.0* texture(normalMapSampler,pass_textureCoords) - 1.0;

	vec3 normalizedVertexNormal = normalize(normalMapValue.rgb);

	if(ShadowsOn==1){
		float shadow_bias = max(0.05 * (1.0-dot(normalizedVertexNormal,normalize(lightVector[0]))),0.005);
		vec3 ndc_shadowCoords = shadowCoords.xyz/shadowCoords.w;
		float closestDepth = texture(shadowMapSampler, ndc_shadowCoords.xy).r;
		shadow = ndc_shadowCoords.z-shadow_bias>closestDepth ? 1. : 0.;
		if(ndc_shadowCoords.z>1.0)
		{
			shadow= 0;
		}
	}



	vec3 totalDifuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for(int i=0;i<4;i++){
		float distance= length(lightVector[i]);
		float attFact = LightAttenuation[i].x + (LightAttenuation[i].y * distance) + (LightAttenuation[i].z * distance * distance);
		vec3 lightDir = normalize(lightVector[i]);
		float lambert = dot(normalizedVertexNormal,lightDir);
		float brightness = max(lambert,0.0);
		vec3 refDir = reflect(-lightDir,normalizedVertexNormal);
		float gloss = max(dot(refDir,camVector),0.0);
		float glossDamped = pow(gloss,GlossDamping);
		totalDifuse	+=(brightness*LightColor[i]*LightIntensity[i])/attFact;
		totalSpecular += (glossDamped * LightColor[i] * Shininess*LightIntensity[i])/attFact;
	}

	totalDifuse = max(totalDifuse,AmbientLightIntensity) * (1.0 - shadow);

	if(length(totalSpecular)<=0) totalSpecular = vec3(0);
	vec4 finalColor = vec4(totalDifuse,1.0) * texture(textureSampler,pass_textureCoords)+vec4(totalSpecular,1.0);
	output_color = mix(finalColor,vec4(FogColor,1),1-fog);
	output_color = finalColor;
}