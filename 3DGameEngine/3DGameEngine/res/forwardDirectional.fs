#version 330
#include "./res/lighting.glh"

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

uniform sampler2D diffuse;
uniform DirectionalLight directionalLight;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) * calcDirectionalLight(directionalLight, normalize(normal0), worldPos0);

    //gl_FragColor = texture * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
	//gl_FragColor = color;
    //gl_FragColor = texture * color;
}

