#version 330

in vec4 texColor;
in vec2 texCoord0;
in vec3 normal0;


//out vec4 fragColor;
// if we use "attribute vec3 position; " in the vertex shader instead of "layout (location = 0) in vec3 position;", 
//then we should not use "out vec4 fragColor;" in the fragment shader.

uniform vec3 basicColor;
uniform sampler2D diffuse;

void main()
{
	
	vec4 textureColor = texture2D(diffuse, texCoord0);
	vec3 normal =normalize(normal0);

    gl_FragColor = textureColor;
}	
