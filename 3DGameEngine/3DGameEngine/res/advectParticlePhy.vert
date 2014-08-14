#version 330                                                                        
                                                                                    
layout (location = 0) in float Type;                                                
layout (location = 1) in vec3 Position;                                             
layout (location = 2) in vec3 Velocity;                                             
layout (location = 3) in float Age;                                                 
                                                                                    
out float Type0;                                                                    
out vec3 Position0;                                                                 
out vec3 Velocity0;                                                                 
out float Age0;                                                                     
out vec3 worldPos; 
                
uniform mat4 T_model;

uniform sampler3D vectorField;
uniform vec3 Extent;

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
    Type0 = Type;                                                                   
    Position0 = SampleVelocity(Position);                                                           
    Velocity0 = Velocity;                                                           
    Age0 = Age;       
	worldPos =  (T_model * vec4(Position, 1.0)).xyz;                                                              
}