#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

uniform mat4 T_transform;
uniform mat4 T_Normal;

void main()
{
	gl_Position = T_transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (T_Normal * vec4(normal, 0.0)).xyz;
	worldPos0 = (T_Normal * vec4(position, 1.0)).xyz;
}