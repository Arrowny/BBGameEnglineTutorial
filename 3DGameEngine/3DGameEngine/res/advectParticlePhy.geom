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

uniform sampler3D vectorField;
uniform vec3 Extent;
uniform float PlumeCeiling;
uniform float InitialBand;
uniform float SeedRadius;
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

vec3 SampleVelocity(vec3 p)
{
    vec3 tc;
    tc.x = (p.x + Extent.x) / (2 * Extent.x);
    tc.y = (p.y + Extent.y) / (2 * Extent.y);
    tc.z = (p.z + Extent.z) / (2 * Extent.z);
    return texture(vectorField, tc).xyz;
}

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

			uint seedx = uint(P_randomSeed.x);
			uint seedy = uint(P_randomSeed.y); 
			uint seedz = uint(P_randomSeed.z); 

			float theta = randhashf(seedy, TwoPi);
			float r = randhashf(seedx, SeedRadius);
			float y = randhashf( seedz, InitialBand);

			TFB_Position.x = r * cos(theta) + P_randomSeed.x*0.33;
			TFB_Position.y = PlumeBase + y + P_randomSeed.y*0.33;
			TFB_Position.z = sin(theta) + P_randomSeed.z*0.33;

			TFB_Type = PARTICLE_TYPE;
			TFB_Position = (T_model * vec4(TFB_Position, 1.0)).xyz;
			TFB_Velocity = P_randomSeed * (ii+1)*10;
			TFB_Age = 0.0;
			EmitVertex();
		}
	}
	else if ( Age0[0] < 5.0 )
	{

		TFB_Type = Type0[0]; 
		if(Position0[0].y < PlumeCeiling)
		{                                                             
			TFB_Velocity = SampleVelocity(Position0[0])*5;                                                           
			vec3 midx = Position0[0] + 0.5 * P_delta * TFB_Velocity;
			TFB_Velocity = SampleVelocity(midx)*5;  
			TFB_Position = Position0[0] + P_delta * TFB_Velocity;    
		}
		else
		{
			TFB_Velocity = Velocity0[0]*P_randomSeed;
			TFB_Position += P_delta * TFB_Velocity;
		}
		
		TFB_Age += P_delta;

		EmitVertex();
	}

	EndPrimitive();
}