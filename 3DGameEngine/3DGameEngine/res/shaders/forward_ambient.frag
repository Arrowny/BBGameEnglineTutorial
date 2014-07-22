#version 330

in vec2 textCoord0;
layout(location = 0) out vec4 fragColor;

uniform sampler2D R_diffuse;
uniform vec3 R_ambientIntensity;

void main()
{
	vec4 textureColor = texture(R_diffuse, textCoord0);
	fragColor = textureColor*vec4(R_ambientIntensity,1.0);
}