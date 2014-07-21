#version 330
#include "lighting.glh"

layout(location = 0) out vec4 fragColor;
in vec2 textCoord0;
in vec3 normal0;
in vec3 worldPos0;

uniform sampler2D diffuse;
uniform SpotLight sLight;

void main()
{
	vec3 normal = normalize(normal0);
	fragColor = texture(diffuse, textCoord0) * calcSpotLight(sLight, normal, worldPos0);
}