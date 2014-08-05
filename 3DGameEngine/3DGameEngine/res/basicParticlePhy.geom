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
	//for(int ii = 0; ii < 100; ii++)
	//{

	////}
	TFB_Type = 0.0;
	TFB_Position = Position0[0] + P_randomSeed/100;
	TFB_Velocity = vec3(0,0.01,0);
	TFB_Age = 0;
	EmitVertex();
	EndPrimitive();

	//if(Type0[0] == EMITTER_TYPE)
	//{
	//	for(int ii = 0; ii < 10; ii++)
	//	{
	//		TFB_Type = PARTICLE_TYPE;
	//		TFB_Position = Position0[0];
	//		//Velocity1.x = P_randomSeed.x * ii;
	//		//Velocity1.y = P_randomSeed.y * ii;
	//		//Velocity1.z = P_randomSeed.z * ii;
	//		TFB_Velocity = P_randomSeed * ii;
	//		normalize(TFB_Velocity);
	//		TFB_Age = 0;
	//		EmitVertex();
	//	}
		
	//}
	//else if (Age0[0] < 100.0)
	//{
	//	TFB_Type = Type0[0];
	//	TFB_Position = Position0[0] + (Velocity0[0] * P_delta);
	//	TFB_Velocity = Velocity0[0];
	//	TFB_Age = Age0[0];
	//	TFB_Age += P_delta;
	//	EmitVertex();
	//}
	//EndPrimitive();
}