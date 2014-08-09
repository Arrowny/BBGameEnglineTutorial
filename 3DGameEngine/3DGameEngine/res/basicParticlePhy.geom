#version 330  

#define EMITTER_TYPE 0
#define PARTICLE_TYPE 1                                                                     
                                                                                    
layout(points) in;                                                                  
layout(points) out;                                                                 
layout(max_vertices = 30) out;                                                      
                                                                                    
in int Type0[];                                                                   
in vec3 Position0[];                                                                
in vec3 Velocity0[];                                                                
in float Age0[];   
in vec3 worldPos[];

out int TFB_Type;                                                                    
out vec3 TFB_Position;                                                                 
out vec3 TFB_Velocity;                                                                 
out float TFB_Age; 

uniform float P_delta;   
uniform vec3 P_randomSeed;

void main()
{
	if(Type0[0] == EMITTER_TYPE)
	{
		TFB_Type = EMITTER_TYPE;
		TFB_Position = Position0[0];
		TFB_Velocity = Velocity0[0];
		TFB_Age = 0.0;
		EmitVertex();


		TFB_Type = PARTICLE_TYPE;
		TFB_Position = worldPos[0];
		TFB_Velocity = P_randomSeed * 10;
		normalize(TFB_Velocity);
		TFB_Age = 0.0;
		EmitVertex();
	}
	else if (Age0[0] < 2.0)
	{
		TFB_Type = Type0[0];
		TFB_Position = Position0[0] + (Velocity0[0] * P_delta);
		TFB_Velocity = Velocity0[0];
		TFB_Age = Age0[0];
		TFB_Age += P_delta;
		EmitVertex();
	}
	EndPrimitive();
}