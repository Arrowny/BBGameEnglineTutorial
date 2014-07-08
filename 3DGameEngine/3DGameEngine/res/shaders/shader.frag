#version 400


in vec2 textCoord0;
layout(location = 0) out fragColor;

uniform sampler2D diffuse;
uniform vec3 color;
uniform bool isTextured;



void main()
{
	vec4 textureColor = texture(diffuse, textCoord0);
	

	if(isTextured)
	{
		fragColor = textureColor*vec4(color,1.0);
	}
	else
	{
		fragColor = vec4(color,1.0);
	}
}