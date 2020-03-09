#version 400 core

in vec3 lightVector[4];
in vec2 pass_textureCoords;
in vec3 camVector;
in float fog;
uniform sampler2D textureSampler;
uniform sampler2D normalMapSampler;
out vec4 output_color;

uniform vec3 LightColor[4];
uniform vec3 LightAttenuation[4];
uniform float LightIntensity[4];

uniform float Shininess;
uniform float GlossDamping;
uniform vec3 FogColor;
uniform float AmbientLightIntensity;

void main(void){
	vec4 normalMapValue = 2.0* texture(normalMapSampler,pass_textureCoords) - 1.0;

	vec3 normalizedVertexNormal = normalize(normalMapValue.rgb);

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

	totalDifuse = max(totalDifuse,AmbientLightIntensity);

	if(length(totalSpecular)<=0) totalSpecular = vec3(0);
	vec4 finalColor = vec4(totalDifuse,1.0) * texture(textureSampler,pass_textureCoords)+vec4(totalSpecular,1.0);
	output_color = mix(finalColor,vec4(FogColor,1),1-fog);
}