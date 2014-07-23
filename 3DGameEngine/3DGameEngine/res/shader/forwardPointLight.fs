#version 330
#include "./res/shader/lighting.glh"

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

//uniform vec3 eyePos;
uniform sampler2D diffuse;
uniform PointLight pointLight;



void main()
{
	//vec4 totalLight = vec4(0,0,0,1);
	//vec4 color = texture2D(diffuse, texCoord0);
	//vec3 normal =normalize(normal0);

	// totalLight += calcPointLight(pointLight,normal);

    //gl_FragColor = color * totalLight;

    gl_FragColor = texture2D(diffuse, texCoord0.xy) * calcPointLight(pointLight, normalize(normal0), worldPos0);
}	
