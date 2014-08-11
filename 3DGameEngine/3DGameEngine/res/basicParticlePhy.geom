#version 400  

#define EMITTER_TYPE 1.0
#define PARTICLE_TYPE 0.0                                                                     
                                                                                    
layout(points) in;                                                                  
layout(points) out;                                                                 
layout(max_vertices = 10) out;                                                      
                                                                                    
in float Type0[];                                                                   
in vec3 Position0[];                                                                
in vec3 Velocity0[];                                                                
in float Age0[];   

out float TFB_Type;                                                                    
out vec3 TFB_Position;                                                                 
out vec3 TFB_Velocity;                                                                 
out float TFB_Age; 

uniform float P_delta;   
uniform vec3 P_randomSeed;
uniform mat4 T_model;  
uniform int numEmit;

void main()
{
	vec3 emit_position = Position0[0];
	int BASE_TYPE = 1;
	if(Type0[0] == EMITTER_TYPE)
	{
		TFB_Type = EMITTER_TYPE;
		TFB_Position = emit_position;
		TFB_Velocity = Velocity0[0];
		TFB_Age = 0.0;
		EmitVertex();

		for(int ii = 0; ii < numEmit; ii++)
		{
			TFB_Type = PARTICLE_TYPE;
			TFB_Position = (T_model * vec4(emit_position, 1.0)).xyz;;
			TFB_Velocity = P_randomSeed * (ii+1)*10;
			TFB_Age = 0.0;
			EmitVertex();
		}
	}
	else if ( Age0[0] < 0.5 )
	{
		TFB_Type = Type0[0];
		TFB_Position = Position0[0] + (Velocity0[0] * P_delta);
		TFB_Velocity = Velocity0[0];
		TFB_Age = Age0[0] + P_delta;
		EmitVertex();
	}
	EndPrimitive();
}