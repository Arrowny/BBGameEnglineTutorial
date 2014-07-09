#version 400

const int MAX_POINT_LIGHTS = 4;

layout(location = 0) out vec4 fragColor;
in vec2 textCoord0;
in vec3 normal0;
in vec3 worldPos0;

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

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

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	vec3 position;
};


uniform sampler2D diffuse;
uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform bool isTextured;

uniform DirectionalLight dLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform float specularIntensity;
uniform float specularPower;
uniform vec3 eyePos;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);

	vec4 diffuseColor = vec4(0,0,0,0);
	vec4 specularColor = vec4(0,0,0,0);

	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;

		vec3 eyeToPointDirection = normalize(eyePos - worldPos0);
		vec3 reflectDirection = normalize(reflect(direction, normal));
		
		float specularFactor = dot(eyeToPointDirection, reflectDirection);
		specularFactor = pow(specularFactor, specularPower);

		if(specularFactor > 0)
		{
			specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor;
		}
	}

	return diffuseColor + specularColor;

}

vec4 calcDirectionalLight(DirectionalLight dLight, vec3 normal)
{
	return calcLight(dLight.base, -dLight.direction, normal);
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = worldPos0 - pointLight.position;
	float distanceToPoint = length(lightDirection);
	lightDirection = normalize(lightDirection);

	vec4 color = calcLight(pointLight.base, lightDirection, normal);

	float attenuation = pointLight.atten.constant + pointLight.atten.linear * distanceToPoint + pointLight.atten.exponent * distanceToPoint *distanceToPoint + 0.000001;

	return color / attenuation;
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

	for(int ii = 0; ii < MAX_POINT_LIGHTS; ii++)
	{
		totalLight += calcPointLight(pointLights[ii], normal);
	}

	fragColor = color * totalLight;
}