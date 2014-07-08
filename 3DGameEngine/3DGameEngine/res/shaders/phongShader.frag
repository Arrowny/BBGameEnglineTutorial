#version 400

uniform sampler2D diffuse;
uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform bool isTextured;

varying vec2 textCoord0;

void main()
{

	vec4 totalLight = vec4(ambientLight, 1.0);

	vec4 color = vec4(baseColor, 1.0);
	if(isTextured)
	{
		color = texture(diffuse, textCoord0)*color;
	}

	gl_FragColor = color * totalLight;
}