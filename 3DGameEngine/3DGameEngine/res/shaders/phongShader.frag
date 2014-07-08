#version 400

layout(location = 0) out vec4 fragColor;
in vec2 textCoord0;
in vec3 normal0;

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


uniform sampler2D diffuse;
uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform DirectionalLight dLight;
uniform bool isTextured;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float attenuation = dot(normal, -direction);

	vec4 diffuseColor = vec4(0,0,0,0);

	if(attenuation > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * attenuation;
	}

	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight dLight, vec3 normal)
{
	return calcLight(dLight.base, -dLight.direction, normal);
}

void main()
{

	vec4 totalLight = vec4(ambientLight, 1.0);
	vec4 color = vec4(baseColor, 1.0);
	vec4 textureColor = texture(diffuse, textCoord0);
	vec3 normal = normalize(normal0);

	if(isTextured)
	{
		color = textureColor*color;
	}

	totalLight += calcDirectionalLight(dLight, normal);

	fragColor = color * totalLight;
}