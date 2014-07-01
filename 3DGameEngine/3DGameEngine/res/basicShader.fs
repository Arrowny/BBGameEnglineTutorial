#version 330

in vec4 color;

varying vec2 texCoord0;

uniform sampler2D diffuse;

void main()
{
    
    //gl_FragColor = color;
    gl_FragColor = texture2D(diffuse, texCoord0);

}
