#version 330

in vec4 color;

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
uniform vec3 lightDirection;
uniform vec3 ambientLight;

void main()
{

    vec4 texture = texture2D(diffuse, texCoord0);
    vec4 totalLight = vec4(ambientLight, 1.0);

	gl_FragColor = color * texture * totalLight;

    //gl_FragColor = texture * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
	//gl_FragColor = color;
    //gl_FragColor = texture * color;

}
