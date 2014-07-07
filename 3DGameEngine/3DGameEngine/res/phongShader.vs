#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

out vec4 color;

uniform float uniformFloat;
uniform mat4 transform;
uniform mat4 Normal;
uniform vec4 baseColor;

void main()
{
	//color = vec4(clamp(position, 0.0, uniformFloat), 1.0);	// Fade in fade out effect
	color = baseColor;											// Solid color
	
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (Normal * vec4(normal, 0.0)).xyz;
	worldPos0 = (Normal * vec4(position, 1.0)).xyz;

	//normal0 = normal;
	
}
