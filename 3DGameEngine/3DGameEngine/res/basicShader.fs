#version 330

in vec4 color;
in vec2 texCoord0;

//out vec4 fragColor;
// if we use "attribute vec3 position; " in the vertex shader instead of "layout (location = 0) in vec3 position;", 
//then we should not use "out vec4 fragColor;" in the fragment shader.

uniform vec3 basicColor;
uniform sampler2D diffuse;

void main()
{

   // gl_FragColor = color;
   gl_FragColor = texture2D(diffuse, texCoord0) * vec4(basicColor,1.0);
}
