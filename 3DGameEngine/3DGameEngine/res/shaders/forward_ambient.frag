#version 330


in vec2 textCoord0;
layout(location = 0) out vec4 fragColor;

uniform sampler2D diffuse;
uniform vec3 ambientIntensity;


void main()
{
	vec4 textureColor = texture(diffuse, textCoord0);
	fragColor = textureColor*vec4(ambientIntensity,1.0);
}