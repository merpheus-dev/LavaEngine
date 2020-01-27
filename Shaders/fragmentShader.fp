#version 400 core

in vec3 lightVector;
in vec3 vertexNormal;
in vec2 pass_textureCoords;
in vec3 camVector;
uniform sampler2D textureSampler;
out vec4 output_color;

uniform vec3 LightColor;
uniform float Shininess;
uniform float GlossDamping;

void main(void){

	vec3 normalizedVertexNormal = normalize(vertexNormal);
	vec3 lightDir = normalize(lightVector);

	float lambert = dot(normalizedVertexNormal,lightDir);
	float brightness = max(lambert,0.2);
	vec3 diffuse =brightness*LightColor;

	vec3 refDir = reflect(-lightDir,vertexNormal);
	float gloss = max(dot(refDir,camVector),0.0);
	float glossDamped = pow(gloss,GlossDamping);
	vec3 specular = glossDamped * LightColor * Shininess;

	if(length(specular)<=0) specular = vec3(0);
	output_color = vec4(diffuse,1.0) * texture(textureSampler,pass_textureCoords)+vec4(specular,1.0);
}