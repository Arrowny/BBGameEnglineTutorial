#version 400

#define BASE_PARTICLE 0

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices = 4) out;
in int Type0[];    


out vec2 TexCoord;   

uniform mat4 T_LookAt;
uniform mat4 T_P;
uniform vec3 C_eyePos;     
uniform float quadLength;

void main(void){

	
	if(Type0[0] != BASE_PARTICLE) //Don't render base particles. Base particles should be used to seed other particles.
	{
		vec4 normal = gl_in[0].gl_Position - vec4(C_eyePos, 1.0);
		normal = T_LookAt*normal;
	
		vec3 rightAxis 	= cross(normal.xyz, vec3(0,1,0));
		vec3 upAxis 	= cross(rightAxis, normal.xyz);
		rightAxis 		= normalize(rightAxis);
		upAxis			= normalize(upAxis);
	
		float qVariance = (quadLength*0.5f);
		vec4 rightVector 	= vec4(rightAxis.xyz, 1.0f)*qVariance;
		vec4 upVector 		= vec4(upAxis.xyz, 1.0f)*qVariance;
		vec4 particlePos	= T_LookAt*gl_in[0].gl_Position;


		gl_Position = particlePos-rightVector-upVector;
		gl_Position = T_P*gl_Position;
		TexCoord = vec2(0,0);
		EmitVertex();
	
		gl_Position = particlePos+rightVector-upVector;
		gl_Position.x += quadLength;
		gl_Position = T_P*gl_Position;
		TexCoord = vec2(1,0);
		EmitVertex();
	
		gl_Position = particlePos-rightVector+upVector;
		gl_Position.y += quadLength;
		gl_Position = T_P*gl_Position;
		TexCoord = vec2(0,1);
		EmitVertex();
	
		gl_Position = particlePos+rightVector+upVector;
		gl_Position.y += quadLength;
		gl_Position.x += quadLength;
		gl_Position = T_P*gl_Position;
		TexCoord = vec2(1,1);
		EmitVertex();
	}
}