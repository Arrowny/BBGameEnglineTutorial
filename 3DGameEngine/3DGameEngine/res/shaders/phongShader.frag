#version 400

uniform sampler2D diffuse;
uniform vec3 color;
uniform bool isTextured;

varying vec2 textCoord0;

void main()
{
	vec4 textureColor = texture(diffuse, textCoord0);
	

	if(isTextured)
	{
		gl_FragColor = textureColor*vec4(color,1.0);
	}
	else
	{
		gl_FragColor = vec4(color,1.0);
	}
}