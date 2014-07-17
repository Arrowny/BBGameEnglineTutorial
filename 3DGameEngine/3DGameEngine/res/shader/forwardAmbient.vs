#version 330

layout (location = 0) in vec3 position;
layout (location =1 ) in vec2 texCoord;

out vec4 color;
out vec2 texCoord0;

uniform mat4 MVP;

void main()
{
	//color =  vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
}