#version 400

attribute vec3 position;
attribute vec2 textCoord;

uniform mat4 transform;

varying vec2 textCoord0;

void main()
{
	//pointColor = vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = transform*vec4(position, 1.0f);
	textCoord0 = textCoord;
}