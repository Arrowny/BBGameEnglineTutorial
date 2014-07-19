#version 330

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 T_transform;

void main()
{	
	gl_Position = T_transform * vec4(position, 1.0);
	texCoord0 = texCoord;
}
