
#version 330

//in vec4 color;
in vec2 texCoord0;

uniform vec3 color;
uniform sampler2D diffuse;

out vec4 fragColor;
// if we use "attribute vec3 position; " in the vertex shader instead of "layout (location = 0) in vec3 position;", 
//then we should not use "out vec4 fragColor;" in the fragment shader.

void main()
{
    vec4 textureColor= texture2D(diffuse, texCoord0.xy);

    if(textureColor == 0)
    {
        gl_FragColor = vec4(color,1);
    }
    else
    {
        gl_FragColor = texture2D(diffuse, texCoord0.xy) * vec4(color,1);
    }
  

}


////===============vertext shader================================
//#version 120
//
//attribute vec3 position;
//attribute vec2 texCoord;
//
//varying vec2 texCoord0;
//uniform mat4 transform;
//
//void main()
//{
//	gl_Position =  transform * vec4(position, 1.0);
//	texCoord0 = texCoord;
//}
//


////=================fragment shader==============================
//#version 120
//
//varying vec2 texCoord0;
//uniform sampler2D diffuse;
//
//
//void main()
//{
//	gl_FragColor = texture2D(diffuse, texCoord0);
//}