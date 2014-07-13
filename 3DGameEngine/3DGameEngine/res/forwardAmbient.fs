#version 330

varying vec2 texCoord0;

uniform sampler2D diffuse;
uniform vec3 ambientLight;

void main()
{
    
    //gl_FragColor = color;
    //gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
    //gl_FragColor = texture2D(diffuse, texCoord0) * color;
    gl_FragColor = texture2D(diffuse, texCoord0) * vec4(ambientLight, 1);

}