#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 normal;
out vec2 textCoord0;
out vec3 normal0;


uniform mat4 transformProjected;
uniform mat4 transformWorld;

void main()
{
	gl_Position = transformProjected*vec4(position, 1.0f);
	textCoord0 = textCoord;
	normal0 = (transformWorld * vec4(normal,0.0)).xyz;
}