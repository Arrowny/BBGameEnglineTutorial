#version 330                                                                        
                                                                                    
layout (location = 0) in int Type;                                                
layout (location = 1) in vec3 Position;                                             
layout (location = 2) in vec3 Velocity;                                             
layout (location = 3) in float Age;                                                 
                                                                                    
out int Type0;                                                                    
out vec3 Position0;                                                                 
out vec3 Velocity0;                                                                 
out float Age0; 
out vec3 worldPos; 
                
uniform mat4 T_model;                                                   
                                                                                    
void main()                                                                         
{                                                                                   
    Type0 = Type;                                                                   
    Position0 = Position;                                                           
    Velocity0 = Velocity;                                                           
    Age0 = Age;
	worldPos =  (T_model * vec4(Position, 1.0)).xyz;       
	//worldPos = Position;                                                    
}