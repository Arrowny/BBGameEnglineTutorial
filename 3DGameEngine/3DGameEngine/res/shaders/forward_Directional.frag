#version 330
#include "lighting.glh"

layout(location = 0) out vec4 fragColor;
in vec2 textCoord0;
in vec3 normal0;
in vec3 worldPos0;

uniform sampler2D R_diffuse;
uniform DirectionalLight R_dLight;

void main()
{
	vec3 normal = normalize(normal0);
	fragColor = texture(R_diffuse, textCoord0) * calcDirectionalLight(R_dLight, normal, worldPos0);
}