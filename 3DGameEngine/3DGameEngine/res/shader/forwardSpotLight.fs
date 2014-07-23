#version 330
#include "./res/shader/lighting.glh"

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

uniform sampler2D diffuse;

uniform SpotLight spotLight;


void main()
{
	vec4 totalLight = vec4(0,0,0,1);
	vec4 color = texture2D(diffuse, texCoord0);
	vec3 normal =normalize(normal0);

	 totalLight += calcSpotLight(spotLight,normal, worldPos0);

    gl_FragColor = color * totalLight;
}	
