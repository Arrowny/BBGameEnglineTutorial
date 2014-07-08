#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
out vec2 textCoord0;

uniform mat4 transform;



void main()
{
	//pointColor = vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = transform*vec4(position, 1.0f);
	textCoord0 = textCoord;
}