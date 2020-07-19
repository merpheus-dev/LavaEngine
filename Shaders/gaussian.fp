#version 400 core
out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D colorTexture;
uniform bool horizontal;

uniform float kernels[11] = float[](
	0.0093,   0.028002, 0.065984,
	0.121703, 0.175713, 0.198596,
	0.175713, 0.121703, 0.065984,
	0.028002, 0.0093
);

void main()
{
	vec3 color = texture( colorTexture , texCoords ).rgb * kernels[0];

	vec2 texelSize = 1.0 / textureSize( colorTexture , 0 );

	if(horizontal)
	{
		for( int i =- 5; i <= 5; ++i )
		{
			color += texture( colorTexture , texCoords + vec2( texelSize.x * i , 0.0) ).rgb * kernels[i+5];
		}
	}
	else
	{
		for( int i =- 5; i <=5; ++i)
		{
			color += texture( colorTexture , texCoords + vec2( 0.0 , texelSize.y * i ) ).rgb * kernels[i+5];
		}
	}

	//Return Frag
	FragColor = vec4( color, 1.0 );
}