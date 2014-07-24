#version 330
#include "./res/shader/lighting.glh"

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

uniform sampler2D diffuse;
uniform DirectionalLight R_directionalLight;

void main()
{
	vec4 totalLight = vec4(0,0,0,1);
	vec4 color = texture2D(diffuse, texCoord0);
	vec3 normal =normalize(normal0);


  	totalLight += calcDirectionalLight(R_directionalLight,normal,worldPos0);

    gl_FragColor = color * totalLight;
}	
