#version 330

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 T_model;

void main()
{	
	gl_Position = T_model * vec4(position, 1.0);
	texCoord0 = texCoord;
}
