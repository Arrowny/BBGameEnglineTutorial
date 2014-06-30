#version 120

attribute vec3 position;

out vec4 color;

uniform float uniformFloat;
uniform mat4 transform;

void main()
{
	color = vec4(clamp(position, 0.0, uniformFloat), 1.0); // Fade in fade out effect
	//color = vec4(clamp(position, 0.0, 1.0), 1.0);			// Solid color
	gl_Position = transform * vec4(position, 1.0);
}
