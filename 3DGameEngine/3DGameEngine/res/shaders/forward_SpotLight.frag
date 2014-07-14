#version 330

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
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

layout(location = 0) out vec4 fragColor;
in vec2 textCoord0;
in vec3 normal0;
in vec3 worldPos0;

uniform sampler2D diffuse;
uniform float specularIntensity;
uniform float specularPower;
uniform SpotLight sLight;
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
	vec3 normal = normalize(normal0);
	fragColor = texture(diffuse, textCoord0) * calcSpotLight(sLight, normal);
}