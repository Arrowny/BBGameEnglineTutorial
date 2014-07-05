#version 330

in vec4 color;

varying vec2 texCoord0;
varying vec3 normal0;

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
uniform vec3 lightDirection;
uniform vec3 ambientLight;

uniform DirectionalLight directionalLight;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
    float diffuseFactor = dot(-direction, normal);

    vec4 diffuseColor = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0)
    {
        diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
    }

    return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
    return calcLight(directionalLight.base, directionalLight.direction, normal);
}

void main()
{

    vec4 texture = texture2D(diffuse, texCoord0);
    vec4 totalLight = vec4(ambientLight, 1.0);

    vec3 normal = normalize(normal0);

    totalLight += calcDirectionalLight(directionalLight, normal);

	gl_FragColor = color * texture * totalLight;

    //gl_FragColor = texture * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
	//gl_FragColor = color;
    //gl_FragColor = texture * color;

}
