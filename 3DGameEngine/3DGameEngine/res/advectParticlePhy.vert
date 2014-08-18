#version 330                                                                        
 
#define EMITTER_TYPE 1.0
#define PARTICLE_TYPE 0.0     
                                                                                
layout (location = 0) in float Type;                                                
layout (location = 1) in vec3 Position;                                             
layout (location = 2) in vec3 Velocity;                                             
layout (location = 3) in float Age;                                                 
                                                                                    
out float Type0;                                                                    
out vec3 Position0;                                                                 
out vec3 Velocity0;                                                                 
out float Age0;                                                                     

uniform float P_delta;
uniform vec3 P_randomSeed;
uniform float InitialBand;
//uniform float SeedRadius;
uniform float PlumeCeiling;
uniform float PlumeBase;

const float TwoPi = 6.28318530718;
const float UINT_MAX = 4294967295.0;

uint randhash(uint seed)
{
    uint i=(seed^12345391u)*2654435769u;
    i^=(i<<6u)^(i>>26u);
    i*=2654435769u;
    i+=(i<<5u)^(i>>12u);
    return i;
}

float randhashf(uint seed, float b)
{
    return float(b * randhash(seed)) / UINT_MAX;
}
                                                             
void main()                                                                         
{      
	Type0 = Type;                                                                   
    Position0 = Position;                                                           
    Velocity0 = Velocity;                                                           
    Age0 = Age;         
	       
	//if (Type == EMITTER_TYPE) 
	//{
	//	uint seedx = uint(P_randomSeed.x);
	//	uint seedy = uint(P_randomSeed.y); 
	//	uint seedz = uint(P_randomSeed.z); 
	//	uint seed = uint(P_delta * 1000.0) + uint(gl_VertexID);
	//	float theta = randhashf(seedy, TwoPi);
	//	float r = randhashf(seedx, SeedRadius);
	//	float y = randhashf( seedz, InitialBand);
	//	Position0.x = r * cos(theta);
	//	Position0.y = PlumeBase + y;
	//	Position0.z = r * sin(theta);
	//	Age0 = 0.0;
 //   }                                                                                                 
}