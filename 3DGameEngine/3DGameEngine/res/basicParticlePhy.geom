#version 330  
#define EMITTER_TYPE 1
#define PARTICLE_TYPE 0                                                                      
                                                                                    
layout(points) in;                                                                  
layout(points) out;                                                                 
layout(max_vertices = 30) out;                                                      
                                                                                    
in float Type0[];                                                                   
in vec3 Position0[];                                                                
in vec3 Velocity0[];                                                                
in float Age0[];   

out float TFB_Type;                                                                    
out vec3 TFB_Position;                                                                 
out vec3 TFB_Velocity;                                                                 
out float TFB_Age; 

//uniform float P_delta;   
uniform vec3 P_randomSeed;

void main()
{

	TFB_Type = 0.0;
	TFB_Position = Position0[0] + P_randomSeed/100;
	TFB_Velocity = vec3(0,0.01,0);
	TFB_Age = 0;
	EmitVertex();
	EndPrimitive();
}