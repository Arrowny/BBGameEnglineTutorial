#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;


out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;

uniform mat4 T_model;
uniform mat4 T_MVP;

void main()
{
	//texColor =  vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = T_MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (T_model * vec4(normal,0.0)).xyz;
	worldPos0 = (T_model * vec4(position,1.0)).xyz;
}
