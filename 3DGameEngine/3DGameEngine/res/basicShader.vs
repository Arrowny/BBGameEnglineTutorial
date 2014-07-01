#version 120

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

out vec4 color;

uniform float uniformFloat;
uniform mat4 transform;

void main()
{
	color = vec4(clamp(position, 0.0, uniformFloat), 1.0); // Fade in fade out effect
	//color = vec4(clamp(position, 0.0, 1.0), 1.0);			// Solid color
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;

}
