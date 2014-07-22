#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
out vec2 textCoord0;

uniform mat4 T_MVP;

void main()
{
	gl_Position = T_MVP*vec4(position, 1.0f);
	textCoord0 = textCoord;
}