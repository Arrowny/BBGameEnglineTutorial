#version 330

attribute vec3 position;

uniform mat4 T_MVP;

out vec3 TexCoord0;

void main()
{
    vec4 MVP_Pos = T_MVP * vec4(position, 1.0);
    gl_Position = MVP_Pos.xyww;
    TexCoord0 = position;
}