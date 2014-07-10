#version 330

in vec4 texColor;
in vec2 texCoord0;
in vec3 normal0;
//out vec4 fragColor;
// if we use "attribute vec3 position; " in the vertex shader instead of "layout (location = 0) in vec3 position;", 
//then we should not use "out vec4 fragColor;" in the fragment shader.
struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

uniform vec3 basicColor;
uniform vec3 ambientLight;
uniform sampler2D diffuse;

uniform DirectionalLight directionalLight;


vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal , -direction);
	vec4 diffuseColor = vec4(0,0,0,0);

	if(diffuseFactor > 0)
	{
		diffuseColor =  vec4(base.color,1.0) * base.intensity * diffuseFactor;
	}
	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{

	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}
void main()
{
	vec4 totalLight = vec4(ambientLight,0.5);
	vec4 color = vec4(basicColor,0.5);
	vec4 textureColor = texture2D(diffuse, texCoord0);
	if(textureColor != vec4(0,0,0,0))
		color = textureColor * color;
  	
  	vec3 normal =normalize(normal0);
  	totalLight += calcDirectionalLight(directionalLight,normal);


    gl_FragColor = color * totalLight;
}	
