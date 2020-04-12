#version 400 core

in vec2 currentSheetCoords;
in vec2 nextSheetCoords;
in float sheetBlend;

uniform sampler2D textureAtlas;

out vec4 color;

void main(void){
	vec4 currentSheet = texture(textureAtlas,currentSheetCoords);
	vec4 nextSheet = texture(textureAtlas,nextSheetCoords);

	color = mix(currentSheet,nextSheet,sheetBlend);
}