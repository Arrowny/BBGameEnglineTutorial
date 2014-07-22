#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 normal;
out vec2 textCoord0;
out vec3 normal0;
out vec3 worldPos0;


uniform mat4 T_MVP;
uniform mat4 T_model;

void main()
{
	gl_Position = T_MVP*vec4(position, 1.0f);
	textCoord0 = textCoord;
	normal0 = (T_model * vec4(normal,0.0)).xyz;
	worldPos0 = (T_model * vec4(position,1.0)).xyz;
}