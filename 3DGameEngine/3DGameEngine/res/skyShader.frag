#version 330

in vec3 TexCoord0;

out vec4 FragColor;

uniform samplerCube diffuse;

void main()
{
    FragColor = texture(diffuse, TexCoord0);
}