#version 330
#extension GL_EXT_geometry_shader4 : enable

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 TexCoord;   

uniform mat4 T_LookAt;
uniform mat4 T_P;
uniform vec3 C_eyePos;     
//uniform float 	quadLength; TODO: add to physicsVariables

void main(void){

	float quadLength = 0.1f;
	vec4 normal = gl_in[0].gl_Position - vec4(C_eyePos, 1.0);
	normal = T_LookAt*normal;
	
	vec3 rightAxis 	= cross(normal.xyz, vec3(0,1,0));
	vec3 upAxis 	= cross(rightAxis, normal.xyz);
	rightAxis 		= normalize(rightAxis);
	upAxis			= normalize(upAxis);
	
	vec4 rightVector 	= vec4(rightAxis.xyz, 1.0f);
	vec4 upVector 		= vec4(upAxis.xyz, 1.0f);
	vec4 particlePos	= T_LookAt*gl_in[0].gl_Position;


	gl_Position = particlePos-rightVector*(quadLength*0.5f)-upVector*(quadLength*0.5f);
	gl_Position = T_P*gl_Position;
	TexCoord = vec2(0,0);
	EmitVertex();
	
	gl_Position = particlePos+rightVector*(quadLength*0.5f)-upVector*(quadLength*0.5f);
	gl_Position.x += 0.5;
	gl_Position = T_P*gl_Position;
	TexCoord = vec2(1,0);
	EmitVertex();
	
	gl_Position = particlePos-rightVector*(quadLength*0.5f)+upVector*(quadLength*0.5f);
	gl_Position.y += 0.5;
	gl_Position = T_P*gl_Position;
	TexCoord = vec2(0,1);
	EmitVertex();
	
	gl_Position = particlePos+rightVector*(quadLength*0.5f)+upVector*(quadLength*0.5f);
	gl_Position.y += 0.5;
	gl_Position.x += 0.5;
	gl_Position = T_P*gl_Position;
	TexCoord = vec2(1,1);
	EmitVertex();
	
}