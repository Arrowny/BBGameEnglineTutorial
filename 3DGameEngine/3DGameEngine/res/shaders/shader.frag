#version 330

in vec4 pointColor;

uniform sampler2D diffuse;

varying vec2 textCoord0;

void main()
{
	//gl_FragColor = pointColor;
	gl_FragColor = texture2D(diffuse, textCoord0);
}