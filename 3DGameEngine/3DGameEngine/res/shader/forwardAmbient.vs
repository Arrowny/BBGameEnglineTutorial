#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

out vec4 color;
out vec2 texCoord0;

uniform mat4 T_MVP;

void main()
{
	//color =  vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = T_MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
}
