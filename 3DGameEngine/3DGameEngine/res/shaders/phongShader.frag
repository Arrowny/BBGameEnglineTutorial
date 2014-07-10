#version 330

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

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
	float range;
};

struct SpotLight
{
	PointLight pLight;
	vec3 direction;
	float cutoff;
};


uniform sampler2D diffuse;
uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform bool isTextured;

uniform DirectionalLight dLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

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

vec4 calcPointLight(PointLight pLight, vec3 normal)
{
	vec3 lightDirection =  pLight.position - worldPos0;
	float distanceToPoint = length(lightDirection);
	
	if(distanceToPoint > pLight.range) //performance optimization
	{
		return vec4(0,0,0,0);
	}

	lightDirection = normalize(lightDirection);

	vec4 color = calcLight(pLight.base, -lightDirection, normal);

	float attenuation = pLight.atten.constant + pLight.atten.linear * distanceToPoint + pLight.atten.exponent * distanceToPoint *distanceToPoint + 0.00001;

	return color / attenuation;
}

vec4 calcSpotLight(SpotLight sLight, vec3 normal)
{
	vec3 lightDirection = normalize(worldPos0 - sLight.pLight.position);
	float spotFactor = dot(lightDirection, sLight.direction);
	
	vec4 color = vec4(0,0,0,0);

	if(spotFactor > sLight.cutoff)
	{
		color = calcPointLight(sLight.pLight, normal) * (1.0 - (1.0 - spotFactor)/(1.0 - sLight.cutoff));
	}

	return color;
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

	//note: dangerous no parentheses
	for(int ii = 0; ii < MAX_POINT_LIGHTS; ii++)
		if(pointLights[ii].base.intensity > 0) //performance optimization
			totalLight += calcPointLight(pointLights[ii], normal);

	//note: dangerous no parentheses
	for(int ii = 0; ii < MAX_SPOT_LIGHTS; ii++)
		if(spotLights[ii].pLight.base.intensity > 0) //performance optimization
			totalLight += calcSpotLight(spotLights[ii], normal);

	fragColor = color * totalLight;
}